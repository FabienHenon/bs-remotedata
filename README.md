# bs-remotedata

`RemoteData` and `WebData` to use with `bs-fetch` and `bs-json` for BuckleScript

![Test status](https://travis-ci.org/FabienHenon/bs-remotedata.svg?branch=master)

`RemoteData.t` is a simple variant type that allows you to store a data that can have 4 potential states:

* `Success('a)`: your data has been successfully retrieved and stored
* `Failure('e)`: your data could not be retrieved
* `Loading`: your data is beeing fetched
* `NotAsked`: you didn't fetch your data yet

This type provides you many usefull functions to handle your data: `map`, `andThen`, `withDefault`, `fromOption`, `fromResult`, `fromPromise`, ...

The main goal for this type is to be used for HTTP requests. That's where `WebData` comes into play.
`WebData.t` is a `RemoteData.t` type but with the error type specified as a `WebData.error`. The `WebData` module provides some usefull functions to fetch data from API and convert it to a `WebData.t`. You can even provide your own _Json_ decoder to convert the result of your API call to a `WebData.t` of any type you want/need.

## Example

```reason
type person = {
  age: int,
  name: string
};

module Decode = {
  let personDecoder = json =>
    Json.Decode.{
      age: json |> field("age", int),
      name: json |> field("name", string)
    };
};

/* At app launch say you set your data state to `NotAsked` */
let data: WebData.t(person) = RemoteData.NotAsked;

/* You received an event and you need to retrieve your data */
let data: WebData.t(person) = RemoteData.Loading;

Fetch.fetch("http://my-api")
|> WebData.fromResponse(Decode.personDecoder)
|> Js.Promise.then_(data => {
  /* Here your data is still a WebData.t(person) and will be
    either Success(person), or Failure(httpError) */
});
```

## Installation

```
npm install --save bs-remotedata
```
Then add `bs-remotedata` to `bs-dependencies` in your `bsconfig.json`:
```
{
  ...
  "bs-dependencies": ["bs-remotedata"]
}
```

## Documentation

For the moment, please see the interface files:

* [RemoteData](src/RemoteData.rei)
* [WebData](src/WebData.rei)

