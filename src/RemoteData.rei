type t('e, 'a) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);

/* Map a function into the Success value */
let map: ('a => 'b, t('e, 'a)) => t('e, 'b);

/* Combine 2 remote data sources with the given function. The result is Success
   if both remote data are Success */
let map2: (('a, 'b) => 'c, t('e, 'a), t('e, 'b)) => t('e, 'c);

/* Put the result of 2 remote data together */
let andMap: (t('e, 'a), t('e, 'a => 'b)) => t('e, 'b);

/* Creates a new remote data with a Success value  */
let succeed: 'a => t('e, 'a);

/* Map a function into the Failure value */
let mapError: ('e => 'f, t('e, 'a)) => t('f, 'a);

/* Map a function into both the Success and the Failure values */
let mapBoth: ('a => 'b, 'e => 'f, t('e, 'a)) => t('f, 'b);

/* Chain remote data function calls only on Success */
let andThen: ('a => t('e, 'b), t('e, 'a)) => t('e, 'b);

/* Return the Success value of the default value */
let withDefault: ('a, t('e, 'a)) => 'a;

/* Convert an option to a remote data with a default error message if option is None */
let fromOption: ('e, option('a)) => t('e, 'a);

/* Convert a remote data to an option */
let toOption: t('e, 'a) => option('a);

/* Convert a Result to a remote data with a default error message if Result is Error */
let fromResult: Belt.Result.t('a, 'e) => t('e, 'a);

/* Convert a Promise result to a Promise that resolves to a remote data */
let fromPromise: ('e, Js.Promise.t('a)) => Js.Promise.t(t('e, 'a));

/* Join 2 remote data into a tuple */
let append: (t('e, 'a), t('e, 'b)) => t('e, ('a, 'b));

/* Convert a list of remote data to a remote data of list */
let fromList: list(t('e, 'a)) => t('e, list('a));

let isSuccess: t('e, 'a) => bool;
let isLoading: t('e, 'a) => bool;
let isFailure: t('e, 'a) => bool;
let isNotAsked: t('e, 'a) => bool;