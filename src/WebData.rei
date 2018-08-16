type error =
  | NetworkError
  | BadStatus(Fetch.Response.t)
  | BadPayload(string, Fetch.Response.t);

type t('a) = RemoteData.t(error, 'a);

/* Convert a Fetch promise to a WebData.t with the text body of the response */
let fromTextResponse:
  Js.Promise.t(Fetch.Response.t) => Js.Promise.t(t(string));

/* Convert a Fetch promise to a WebData.t with the type returned by the decoder you passed */
let fromResponse:
  (Js.Json.t => 'a, Js.Promise.t(Fetch.Response.t)) => Js.Promise.t(t('a));