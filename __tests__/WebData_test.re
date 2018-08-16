open Jest;
open WebData;
open RemoteData;

[@bs.deriving abstract]
type responseStatus = {status: int};

[@bs.val] [@bs.scope "fetch"] external resetMocks: unit => unit = "resetMocks";
[@bs.val] [@bs.scope "fetch"]
external mockResponseOnce: Js.Nullable.t(string) => unit = "mockResponseOnce";
[@bs.val] [@bs.scope "fetch"]
external mockResponseOnceWithStatus:
  (Js.Nullable.t(string), responseStatus) => unit =
  "mockResponseOnce";
[@bs.val] [@bs.scope "fetch"] external mockReject: exn => unit = "mockReject";

let isFailurePayload: WebData.t('a) => bool =
  data =>
    switch (data) {
    | Failure(err) =>
      switch (err) {
      | BadPayload(_, _) => true
      | _ => false
      }
    | _ => false
    };

let isFailureStatus: WebData.t('a) => bool =
  data =>
    switch (data) {
    | Failure(err) =>
      switch (err) {
      | BadStatus(_) => true
      | _ => false
      }
    | _ => false
    };

type testType = {
  age: int,
  name: string,
};

let testTypeDecoder = json =>
  Json.Decode.{
    age: json |> field("age", int),
    name: json |> field("name", string),
  };

describe("WebData", () => {
  beforeEach(() => resetMocks());

  describe("fromTextResponse", () => {
    open Expect;

    testPromise("succeed", () => {
      mockResponseOnce(Js.Nullable.return("my result"));

      Fetch.fetch("http://test")
      |> fromTextResponse
      |> Js.Promise.then_(data =>
           expect(data)
           |> toEqual(Success("my result"))
           |> Js.Promise.resolve
         );
    });

    testPromise("failed request", () => {
      mockReject(Not_found);

      Fetch.fetch("http://test")
      |> fromTextResponse
      |> Js.Promise.then_(data =>
           expect(data)
           |> toEqual(Failure(NetworkError))
           |> Js.Promise.resolve
         );
    });

    testPromise("failed payload", () => {
      mockResponseOnce(Js.Nullable.null);

      Fetch.fetch("http://test")
      |> fromTextResponse
      |> Js.Promise.then_(data =>
           expect(data |> isFailurePayload)
           |> toBe(true)
           |> Js.Promise.resolve
         );
    });

    testPromise("failed status", () => {
      mockResponseOnceWithStatus(
        Js.Nullable.return("result"),
        responseStatus(~status=404),
      );

      Fetch.fetch("http://test")
      |> fromTextResponse
      |> Js.Promise.then_(data =>
           expect(data |> isFailureStatus)
           |> toBe(true)
           |> Js.Promise.resolve
         );
    });
  });

  describe("fromResponse", () => {
    open Expect;

    testPromise("succeed", () => {
      mockResponseOnce(Js.Nullable.return({|{"age": 10, "name": "John"}|}));

      Fetch.fetch("http://test")
      |> fromResponse(testTypeDecoder)
      |> Js.Promise.then_(data =>
           expect(data)
           |> toEqual(Success({age: 10, name: "John"}))
           |> Js.Promise.resolve
         );
    });

    testPromise("failed request", () => {
      mockReject(Not_found);

      Fetch.fetch("http://test")
      |> fromResponse(testTypeDecoder)
      |> Js.Promise.then_(data =>
           expect(data)
           |> toEqual(Failure(NetworkError))
           |> Js.Promise.resolve
         );
    });

    testPromise("failed payload", () => {
      mockResponseOnce(Js.Nullable.null);

      Fetch.fetch("http://test")
      |> fromResponse(testTypeDecoder)
      |> Js.Promise.then_(data =>
           expect(data |> isFailurePayload)
           |> toBe(true)
           |> Js.Promise.resolve
         );
    });

    testPromise("failed status", () => {
      mockResponseOnceWithStatus(
        Js.Nullable.return("result"),
        responseStatus(~status=404),
      );

      Fetch.fetch("http://test")
      |> fromResponse(testTypeDecoder)
      |> Js.Promise.then_(data =>
           expect(data |> isFailureStatus)
           |> toBe(true)
           |> Js.Promise.resolve
         );
    });

    testPromise("failed payload decoder", () => {
      mockResponseOnce(
        Js.Nullable.return({|{"age": "10", "name": "John"}|}),
      );

      Fetch.fetch("http://test")
      |> fromResponse(testTypeDecoder)
      |> Js.Promise.then_(data =>
           expect(data |> isFailurePayload)
           |> toBe(true)
           |> Js.Promise.resolve
         );
    });
  });
});