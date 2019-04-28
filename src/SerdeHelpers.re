let deserialize_Belt_SetString____t = json =>
  switch (Js.Json.classify(json)) {
  | Js.Json.JSONArray(items) =>
    let%Lets.Try items =
      items->Array.reduce(
        Result.Ok([]),
        (current, item) => {
          let%Lets.Try current = current;
          let%Lets.Try item =
            switch (Js.Json.classify(item)) {
            | JSONString(string) => Result.Ok(string)
            | _ => Error(["Expected a string in the Set.String json"])
            };
          Ok([item, ...current]);
        },
      );
    Ok(Set.String.fromArray(items->List.toArray));
  | _ => Error(["Expected an array in the Set.String.json"])
  };

let serialize_Belt_SetString____t = set => {
  let items = set->Set.String.toArray->Array.map(s => Js.Json.string(s));
  Js.Json.array(items);
};