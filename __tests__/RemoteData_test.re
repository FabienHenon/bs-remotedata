open Jest;
open RemoteData;

describe("RemoteData", () => {
  describe("basic", () => {
    open Expect;

    test("succeed", () =>
      expect(succeed(1)) |> toEqual(Success(1))
    );

    test("isSuccess for Success", () =>
      expect(Success(1) |> isSuccess) |> toBe(true)
    );
    test("isSuccess for Failure", () =>
      expect(Failure(1) |> isSuccess) |> toBe(false)
    );
    test("isSuccess for NotAsked", () =>
      expect(NotAsked |> isSuccess) |> toBe(false)
    );
    test("isSuccess for Loading", () =>
      expect(Loading |> isSuccess) |> toBe(false)
    );

    test("isFailure for Success", () =>
      expect(Success(1) |> isFailure) |> toBe(false)
    );
    test("isFailure for Failure", () =>
      expect(Failure(1) |> isFailure) |> toBe(true)
    );
    test("isFailure for NotAsked", () =>
      expect(NotAsked |> isFailure) |> toBe(false)
    );
    test("isFailure for Loading", () =>
      expect(Loading |> isFailure) |> toBe(false)
    );

    test("isLoading for Success", () =>
      expect(Success(1) |> isLoading) |> toBe(false)
    );
    test("isLoading for Failure", () =>
      expect(Failure(1) |> isLoading) |> toBe(false)
    );
    test("isLoading for NotAsked", () =>
      expect(NotAsked |> isLoading) |> toBe(false)
    );
    test("isLoading for Loading", () =>
      expect(Loading |> isLoading) |> toBe(true)
    );

    test("isNotAsked for Success", () =>
      expect(Success(1) |> isNotAsked) |> toBe(false)
    );
    test("isNotAsked for Failure", () =>
      expect(Failure(1) |> isNotAsked) |> toBe(false)
    );
    test("isNotAsked for NotAsked", () =>
      expect(NotAsked |> isNotAsked) |> toBe(true)
    );
    test("isNotAsked for Loading", () =>
      expect(Loading |> isNotAsked) |> toBe(false)
    );
  });

  describe("map", () => {
    open Expect;

    test("with Success", () =>
      expect(Success(1) |> map((+)(1))) |> toEqual(Success(2))
    );
    test("with Failure", () =>
      expect(Failure(1) |> map((+)(1))) |> toEqual(Failure(1))
    );
    test("with Loading", () =>
      expect(Loading |> map((+)(1))) |> toEqual(Loading)
    );
    test("with NotAsked", () =>
      expect(NotAsked |> map((+)(1))) |> toEqual(NotAsked)
    );
  });

  describe("map2", () => {
    open Expect;

    test("with Success and Success", () =>
      expect(Success(1) |> map2((+), Success(1))) |> toEqual(Success(2))
    );
    test("with Success and Failure", () =>
      expect(Success(1) |> map2((+), Failure(1))) |> toEqual(Failure(1))
    );
    test("with Success and Loading", () =>
      expect(Success(1) |> map2((+), Loading)) |> toEqual(Loading)
    );
    test("with Success and NotAsked", () =>
      expect(Success(1) |> map2((+), NotAsked)) |> toEqual(NotAsked)
    );
    test("with Failure and Success", () =>
      expect(Failure(1) |> map2((+), Success(1))) |> toEqual(Failure(1))
    );
    test("with Failure and Failure", () =>
      expect(Failure(1) |> map2((+), Failure(1))) |> toEqual(Failure(1))
    );
    test("with Failure and Loading", () =>
      expect(Failure(1) |> map2((+), Loading)) |> toEqual(Failure(1))
    );
    test("with Failure and NotAsked", () =>
      expect(Failure(1) |> map2((+), NotAsked)) |> toEqual(Failure(1))
    );
    test("with Loading and Success", () =>
      expect(Loading |> map2((+), Success(1))) |> toEqual(Loading)
    );
    test("with Loading and Failure", () =>
      expect(Loading |> map2((+), Failure(1))) |> toEqual(Failure(1))
    );
    test("with Loading and Loading", () =>
      expect(Loading |> map2((+), Loading)) |> toEqual(Loading)
    );
    test("with Loading and NotAsked", () =>
      expect(Loading |> map2((+), NotAsked)) |> toEqual(Loading)
    );
    test("with NotAsked and Success", () =>
      expect(NotAsked |> map2((+), Success(1))) |> toEqual(NotAsked)
    );
    test("with NotAsked and Failure", () =>
      expect(NotAsked |> map2((+), Failure(1))) |> toEqual(Failure(1))
    );
    test("with NotAsked and Loading", () =>
      expect(NotAsked |> map2((+), Loading)) |> toEqual(Loading)
    );
    test("with NotAsked and NotAsked", () =>
      expect(NotAsked |> map2((+), NotAsked)) |> toEqual(NotAsked)
    );
  });

  describe("andMap", () => {
    open Expect;

    test("with Success and Success", () =>
      expect(Success((+)(1)) |> andMap(Success(1)))
      |> toEqual(Success(2))
    );
    test("with Success and Failure", () =>
      expect(Failure(1) |> andMap(Success(1))) |> toEqual(Failure(1))
    );
    test("with Success and Loading", () =>
      expect(Loading |> andMap(Success(1))) |> toEqual(Loading)
    );
    test("with Success and NotAsked", () =>
      expect(NotAsked |> andMap(Success(1))) |> toEqual(NotAsked)
    );
    test("with Failure and Success", () =>
      expect(Success((+)(1)) |> andMap(Failure(1)))
      |> toEqual(Failure(1))
    );
    test("with Failure and Failure", () =>
      expect(Failure(1) |> andMap(Failure(1))) |> toEqual(Failure(1))
    );
    test("with Failure and Loading", () =>
      expect(Loading |> andMap(Failure(1))) |> toEqual(Failure(1))
    );
    test("with Failure and NotAsked", () =>
      expect(NotAsked |> andMap(Failure(1))) |> toEqual(Failure(1))
    );
    test("with Loading and Success", () =>
      expect(Success((+)(1)) |> andMap(Loading)) |> toEqual(Loading)
    );
    test("with Loading and Failure", () =>
      expect(Failure(1) |> andMap(Loading)) |> toEqual(Failure(1))
    );
    test("with Loading and Loading", () =>
      expect(Loading |> andMap(Loading)) |> toEqual(Loading)
    );
    test("with Loading and NotAsked", () =>
      expect(NotAsked |> andMap(Loading)) |> toEqual(Loading)
    );
    test("with NotAsked and Success", () =>
      expect(Success((+)(1)) |> andMap(NotAsked)) |> toEqual(NotAsked)
    );
    test("with NotAsked and Failure", () =>
      expect(Failure(1) |> andMap(NotAsked)) |> toEqual(Failure(1))
    );
    test("with NotAsked and Loading", () =>
      expect(Loading |> andMap(NotAsked)) |> toEqual(Loading)
    );
    test("with NotAsked and NotAsked", () =>
      expect(NotAsked |> andMap(NotAsked)) |> toEqual(NotAsked)
    );
  });

  describe("mapError", () => {
    open Expect;

    test("with Success", () =>
      expect(Success(1) |> mapError((+)(1))) |> toEqual(Success(1))
    );
    test("with Failure", () =>
      expect(Failure(1) |> mapError((+)(1))) |> toEqual(Failure(2))
    );
    test("with Loading", () =>
      expect(Loading |> mapError((+)(1))) |> toEqual(Loading)
    );
    test("with NotAsked", () =>
      expect(NotAsked |> mapError((+)(1))) |> toEqual(NotAsked)
    );
  });

  describe("mapBoth", () => {
    open Expect;

    test("with Success", () =>
      expect(Success(1) |> mapBoth((+)(1), (+)(2)))
      |> toEqual(Success(2))
    );
    test("with Failure", () =>
      expect(Failure(1) |> mapBoth((+)(1), (+)(2)))
      |> toEqual(Failure(3))
    );
    test("with Loading", () =>
      expect(Loading |> mapBoth((+)(1), (+)(2))) |> toEqual(Loading)
    );
    test("with NotAsked", () =>
      expect(NotAsked |> mapBoth((+)(1), (+)(2))) |> toEqual(NotAsked)
    );
  });

  describe("andThen", () => {
    open Expect;

    test("with Success, returning Success", () =>
      expect(Success(1) |> andThen(v => Success(1 + v)))
      |> toEqual(Success(2))
    );
    test("with Success, returning Failure", () =>
      expect(Success(1) |> andThen(_ => Failure(10)))
      |> toEqual(Failure(10))
    );
    test("with Failure", () =>
      expect(Failure(1) |> andThen(v => Success(1 + v)))
      |> toEqual(Failure(1))
    );
    test("with Loading", () =>
      expect(Loading |> andThen(v => Success(1 + v))) |> toEqual(Loading)
    );
    test("with NotAsked", () =>
      expect(NotAsked |> andThen(v => Success(1 + v))) |> toEqual(NotAsked)
    );
  });

  describe("withDefault", () => {
    open Expect;

    test("with Success", () =>
      expect(Success(1) |> withDefault(100)) |> toEqual(1)
    );
    test("with Failure", () =>
      expect(Failure(1) |> withDefault(100)) |> toEqual(100)
    );
    test("with Loading", () =>
      expect(Loading |> withDefault(100)) |> toEqual(100)
    );
    test("with NotAsked", () =>
      expect(NotAsked |> withDefault(100)) |> toEqual(100)
    );
  });

  describe("append", () => {
    open Expect;

    test("with Success and Success", () =>
      expect(Success(1) |> append(Success(1)))
      |> toEqual(Success((1, 1)))
    );
    test("with Failure and Success", () =>
      expect(Failure(1) |> append(Success(1))) |> toEqual(Failure(1))
    );
    test("with Loading and Success", () =>
      expect(Loading |> append(Success(1))) |> toEqual(Loading)
    );
    test("with NotAsked and Success", () =>
      expect(NotAsked |> append(Success(1))) |> toEqual(NotAsked)
    );
    test("with Success and Failure", () =>
      expect(Success(1) |> append(Failure(1))) |> toEqual(Failure(1))
    );
    test("with Failure and Failure", () =>
      expect(Failure(1) |> append(Failure(1))) |> toEqual(Failure(1))
    );
    test("with Loading and Failure", () =>
      expect(Loading |> append(Failure(1))) |> toEqual(Failure(1))
    );
    test("with NotAsked and Failure", () =>
      expect(NotAsked |> append(Failure(1))) |> toEqual(Failure(1))
    );
    test("with Success and Loading", () =>
      expect(Success(1) |> append(Loading)) |> toEqual(Loading)
    );
    test("with Failure and Loading", () =>
      expect(Failure(1) |> append(Loading)) |> toEqual(Failure(1))
    );
    test("with Loading and Loading", () =>
      expect(Loading |> append(Loading)) |> toEqual(Loading)
    );
    test("with NotAsked and Failure", () =>
      expect(NotAsked |> append(Loading)) |> toEqual(Loading)
    );
    test("with Success and NotAsked", () =>
      expect(Success(1) |> append(NotAsked)) |> toEqual(NotAsked)
    );
    test("with Failure and NotAsked", () =>
      expect(Failure(1) |> append(NotAsked)) |> toEqual(Failure(1))
    );
    test("with Loading and NotAsked", () =>
      expect(Loading |> append(NotAsked)) |> toEqual(Loading)
    );
    test("with NotAsked and NotAsked", () =>
      expect(NotAsked |> append(NotAsked)) |> toEqual(NotAsked)
    );
  });

  describe("fromList", () => {
    open Expect;

    test("with at least a Failure", () =>
      expect([Success(1), Failure(1), NotAsked, Loading] |> fromList)
      |> toEqual(Failure(1))
    );
    test("with at least a Loading", () =>
      expect([Success(1), NotAsked, Loading] |> fromList)
      |> toEqual(Loading)
    );
    test("with at least a NotAsked", () =>
      expect([Success(1), NotAsked] |> fromList) |> toEqual(NotAsked)
    );
    test("with only Success", () =>
      expect([Success(1), Success(2)] |> fromList)
      |> toEqual(Success([1, 2]))
    );
  });

  describe("fromOption", () => {
    open Expect;

    test("with Some", () =>
      expect(Some(1) |> fromOption(100)) |> toEqual(Success(1))
    );
    test("with None", () =>
      expect(None |> fromOption(100)) |> toEqual(Failure(100))
    );
  });

  describe("toOption", () => {
    open Expect;

    test("with Success", () =>
      expect(Success(1) |> toOption) |> toEqual(Some(1))
    );
    test("with Failure", () =>
      expect(Failure(1) |> toOption) |> toEqual(None)
    );
    test("with Loading", () =>
      expect(Loading |> toOption) |> toEqual(None)
    );
    test("with NotAsked", () =>
      expect(NotAsked |> toOption) |> toEqual(None)
    );
  });

  describe("fromResult", () => {
    open Expect;

    test("with Some", () =>
      expect(Belt.Result.Ok(1) |> fromResult) |> toEqual(Success(1))
    );
    test("with None", () =>
      expect(Belt.Result.Error(2) |> fromResult) |> toEqual(Failure(2))
    );
  });

  describe("fromPromise", () => {
    open Expect;

    testPromise("with resolved value", () =>
      Js.Promise.(
        resolve(1)
        |> fromPromise(100)
        |> then_(v => expect(v) |> toEqual(Success(1)) |> resolve)
      )
    );
    testPromise("with rejected value", () =>
      Js.Promise.(
        reject(Not_found)
        |> fromPromise(100)
        |> then_(v => expect(v) |> toEqual(Failure(100)) |> resolve)
      )
    );
  });
});