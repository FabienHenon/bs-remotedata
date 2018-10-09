type error =
  | NetworkError
  | BadStatus(Fetch.Response.t)
  | BadPayload(string, Fetch.Response.t);

type t('a) = RemoteData.t(error, 'a);

let handleResponse =
    (
      promise: Js.Promise.t(Fetch.Response.t),
      parser: Fetch.Response.t => Js.Promise.t('a),
      decoder: (Fetch.Response.t, t('a)) => Js.Promise.t(t('b)),
    )
    : Js.Promise.t(t('b)) =>
  Js.Promise.(
    promise
    |> then_(res =>
         if (Fetch.Response.ok(res)) {
           res
           |> parser
           |> RemoteData.fromPromise(
                BadPayload("Impossible to get response body", res),
              )
           |> then_(decoder(res));
         } else {
           RemoteData.Failure(BadStatus(res)) |> resolve;
         }
       )
    |> catch(_ => RemoteData.Failure(NetworkError) |> resolve)
  );

let fromTextResponse = promise =>
  handleResponse(promise, Fetch.Response.text, _ => Js.Promise.resolve);

let handleJsonDecode =
    (
      decoder: Js.Json.t => Belt.Result.t('a, string),
      res: Fetch.Response.t,
      jsonData: t(Js.Json.t),
    )
    : Js.Promise.t(t('a)) =>
  RemoteData.andThen(
    json =>
      switch (decoder(json)) {
      | Belt.Result.Error(err) => RemoteData.Failure(BadPayload(err, res))
      | Belt.Result.Ok(v) => RemoteData.Success(v)
      },
    jsonData,
  )
  |> Js.Promise.resolve;

let fromResponse = (decoder, promise) =>
  handleResponse(promise, Fetch.Response.json, handleJsonDecode(decoder));
