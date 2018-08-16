type t('e, 'a) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);

let map = (func, data) =>
  switch (data) {
  | Success(a) => Success(func(a))
  | NotAsked => NotAsked
  | Loading => Loading
  | Failure(err) => Failure(err)
  };

let andMap = (value, func) =>
  switch (func, value) {
  | (Success(f), Success(v)) => Success(f(v))
  | (Failure(e), _) => Failure(e)
  | (_, Failure(e)) => Failure(e)
  | (Loading, _) => Loading
  | (_, Loading) => Loading
  | (NotAsked, _) => NotAsked
  | (_, NotAsked) => NotAsked
  };

let map2 = (func, a, b) => map(func, a) |> andMap(b);

let succeed = value => Success(value);

let mapError = (func, data) =>
  switch (data) {
  | Success(a) => Success(a)
  | NotAsked => NotAsked
  | Loading => Loading
  | Failure(err) => Failure(func(err))
  };

let mapBoth = (valueFunc, errorFunc, data) =>
  data |> map(valueFunc) |> mapError(errorFunc);

let andThen = (func, data) =>
  switch (data) {
  | Success(a) => func(a)
  | NotAsked => NotAsked
  | Loading => Loading
  | Failure(err) => Failure(err)
  };

let withDefault = (defaultValue, data) =>
  switch (data) {
  | Success(a) => a
  | NotAsked => defaultValue
  | Loading => defaultValue
  | Failure(_) => defaultValue
  };

let fromOption = (defaultError, optionData) =>
  Belt.Option.mapWithDefault(optionData, Failure(defaultError), succeed);

let toOption = data => data |> map(v => Some(v)) |> withDefault(None);

let fromResult = result =>
  switch (result) {
  | Belt.Result.Ok(v) => Success(v)
  | Belt.Result.Error(v) => Failure(v)
  };

let fromPromise = (defaultError, promise) =>
  Js.Promise.(
    promise
    |> then_(v => Success(v) |> resolve)
    |> catch(_ => Failure(defaultError) |> resolve)
  );

let append = (data1, data2) =>
  map((t1, t2) => (t1, t2), data1) |> andMap(data2);

let fromList = dataList =>
  List.fold_right(
    map2((item, rest) => [item, ...rest]),
    dataList,
    Success([]),
  );

let isSuccess = data =>
  switch (data) {
  | Success(_) => true
  | Failure(_) => false
  | NotAsked => false
  | Loading => false
  };

let isFailure = data =>
  switch (data) {
  | Success(_) => false
  | Failure(_) => true
  | NotAsked => false
  | Loading => false
  };

let isLoading = data =>
  switch (data) {
  | Success(_) => false
  | Failure(_) => false
  | NotAsked => false
  | Loading => true
  };

let isNotAsked = data =>
  switch (data) {
  | Success(_) => false
  | Failure(_) => false
  | NotAsked => true
  | Loading => false
  };