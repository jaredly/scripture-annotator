[@ocaml.warning "-34"];
module Types1 = {
  type _Types__reference =
    Types.reference = {
      uri: string,
      start: (int, int),
      stop: (int, int),
    }
  and _Types__Annotation__t =
    Types.Annotation.t = {
      id: string,
      tags: list(string),
      references: list(_Types__reference),
      notes: string,
      created: float,
      modified: float,
    }
  and _Types__Tag__t =
    Types.Tag.t = {
      id: string,
      name: string,
      color: string,
    };
};
let currentVersion = 1;
type target = Js.Json.t;
module Version1 = {
  open Types1;
  let rec deserialize_Types____reference:
    target => Belt.Result.t(_Types__reference, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_stop => {
          let inner = attr_start => {
            let inner = attr_uri =>
              Belt.Result.Ok(
                {uri: attr_uri, start: attr_start, stop: attr_stop}: _Types__reference,
              );
            switch (Js.Dict.get(dict, "uri")) {
            | None => Belt.Result.Error(["No attribute 'uri'"])
            | Some(json) =>
              switch (
                (
                  string =>
                    switch (Js.Json.classify(string)) {
                    | JSONString(string) => Belt.Result.Ok(string)
                    | _ => Error(["expected a string"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'uri'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "start")) {
          | None => Belt.Result.Error(["No attribute 'start'"])
          | Some(json) =>
            switch (
              (
                json =>
                  switch (Js.Json.classify(json)) {
                  | JSONArray([|arg0, arg1|]) =>
                    switch (
                      (
                        number =>
                          switch (Js.Json.classify(number)) {
                          | JSONNumber(number) =>
                            Belt.Result.Ok(int_of_float(number))
                          | _ => Error(["Expected a float"])
                          }
                      )(
                        arg1,
                      )
                    ) {
                    | Belt.Result.Ok(arg1) =>
                      switch (
                        (
                          number =>
                            switch (Js.Json.classify(number)) {
                            | JSONNumber(number) =>
                              Belt.Result.Ok(int_of_float(number))
                            | _ => Error(["Expected a float"])
                            }
                        )(
                          arg0,
                        )
                      ) {
                      | Belt.Result.Ok(arg0) => Belt.Result.Ok((arg0, arg1))
                      | Error(error) =>
                        Belt.Result.Error(["tuple element 0", ...error])
                      }
                    | Error(error) =>
                      Belt.Result.Error(["tuple element 1", ...error])
                    }
                  | _ => Belt.Result.Error(["Expected an array"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'start'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "stop")) {
        | None => Belt.Result.Error(["No attribute 'stop'"])
        | Some(json) =>
          switch (
            (
              json =>
                switch (Js.Json.classify(json)) {
                | JSONArray([|arg0, arg1|]) =>
                  switch (
                    (
                      number =>
                        switch (Js.Json.classify(number)) {
                        | JSONNumber(number) =>
                          Belt.Result.Ok(int_of_float(number))
                        | _ => Error(["Expected a float"])
                        }
                    )(
                      arg1,
                    )
                  ) {
                  | Belt.Result.Ok(arg1) =>
                    switch (
                      (
                        number =>
                          switch (Js.Json.classify(number)) {
                          | JSONNumber(number) =>
                            Belt.Result.Ok(int_of_float(number))
                          | _ => Error(["Expected a float"])
                          }
                      )(
                        arg0,
                      )
                    ) {
                    | Belt.Result.Ok(arg0) => Belt.Result.Ok((arg0, arg1))
                    | Error(error) =>
                      Belt.Result.Error(["tuple element 0", ...error])
                    }
                  | Error(error) =>
                    Belt.Result.Error(["tuple element 1", ...error])
                  }
                | _ => Belt.Result.Error(["Expected an array"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'stop'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types__Annotation__t:
    target => Belt.Result.t(_Types__Annotation__t, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_modified => {
          let inner = attr_created => {
            let inner = attr_notes => {
              let inner = attr_references => {
                let inner = attr_tags => {
                  let inner = attr_id =>
                    Belt.Result.Ok(
                      {
                        id: attr_id,
                        tags: attr_tags,
                        references: attr_references,
                        notes: attr_notes,
                        created: attr_created,
                        modified: attr_modified,
                      }: _Types__Annotation__t,
                    );
                  switch (Js.Dict.get(dict, "id")) {
                  | None => Belt.Result.Error(["No attribute 'id'"])
                  | Some(json) =>
                    switch (
                      (
                        string =>
                          switch (Js.Json.classify(string)) {
                          | JSONString(string) => Belt.Result.Ok(string)
                          | _ => Error(["expected a string"])
                          }
                      )(
                        json,
                      )
                    ) {
                    | Belt.Result.Error(error) =>
                      Belt.Result.Error(["attribute 'id'", ...error])
                    | Ok(data) => inner(data)
                    }
                  };
                };
                switch (Js.Dict.get(dict, "tags")) {
                | None => Belt.Result.Error(["No attribute 'tags'"])
                | Some(json) =>
                  switch (
                    (
                      list =>
                        switch (Js.Json.classify(list)) {
                        | JSONArray(items) =>
                          let transformer = string =>
                            switch (Js.Json.classify(string)) {
                            | JSONString(string) => Belt.Result.Ok(string)
                            | _ => Error(["expected a string"])
                            };
                          let rec loop = (i, collected, items) =>
                            switch (items) {
                            | [] =>
                              Belt.Result.Ok(Belt.List.reverse(collected))
                            | [one, ...rest] =>
                              switch (transformer(one)) {
                              | Belt.Result.Error(error) =>
                                Belt.Result.Error([
                                  "list element " ++ string_of_int(i),
                                  ...error,
                                ])
                              | Belt.Result.Ok(value) =>
                                loop(i + 1, [value, ...collected], rest)
                              }
                            };
                          loop(0, [], Belt.List.fromArray(items));
                        | _ => Belt.Result.Error(["expected an array"])
                        }
                    )(
                      json,
                    )
                  ) {
                  | Belt.Result.Error(error) =>
                    Belt.Result.Error(["attribute 'tags'", ...error])
                  | Ok(data) => inner(data)
                  }
                };
              };
              switch (Js.Dict.get(dict, "references")) {
              | None => Belt.Result.Error(["No attribute 'references'"])
              | Some(json) =>
                switch (
                  (
                    list =>
                      switch (Js.Json.classify(list)) {
                      | JSONArray(items) =>
                        let transformer = deserialize_Types____reference;
                        let rec loop = (i, collected, items) =>
                          switch (items) {
                          | [] =>
                            Belt.Result.Ok(Belt.List.reverse(collected))
                          | [one, ...rest] =>
                            switch (transformer(one)) {
                            | Belt.Result.Error(error) =>
                              Belt.Result.Error([
                                "list element " ++ string_of_int(i),
                                ...error,
                              ])
                            | Belt.Result.Ok(value) =>
                              loop(i + 1, [value, ...collected], rest)
                            }
                          };
                        loop(0, [], Belt.List.fromArray(items));
                      | _ => Belt.Result.Error(["expected an array"])
                      }
                  )(
                    json,
                  )
                ) {
                | Belt.Result.Error(error) =>
                  Belt.Result.Error(["attribute 'references'", ...error])
                | Ok(data) => inner(data)
                }
              };
            };
            switch (Js.Dict.get(dict, "notes")) {
            | None => Belt.Result.Error(["No attribute 'notes'"])
            | Some(json) =>
              switch (
                (
                  string =>
                    switch (Js.Json.classify(string)) {
                    | JSONString(string) => Belt.Result.Ok(string)
                    | _ => Error(["expected a string"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'notes'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "created")) {
          | None => Belt.Result.Error(["No attribute 'created'"])
          | Some(json) =>
            switch (
              (
                number =>
                  switch (Js.Json.classify(number)) {
                  | JSONNumber(number) => Belt.Result.Ok(number)
                  | _ => Error(["Expected a float"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'created'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "modified")) {
        | None => Belt.Result.Error(["No attribute 'modified'"])
        | Some(json) =>
          switch (
            (
              number =>
                switch (Js.Json.classify(number)) {
                | JSONNumber(number) => Belt.Result.Ok(number)
                | _ => Error(["Expected a float"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'modified'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types__Tag__t:
    target => Belt.Result.t(_Types__Tag__t, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_color => {
          let inner = attr_name => {
            let inner = attr_id =>
              Belt.Result.Ok(
                {id: attr_id, name: attr_name, color: attr_color}: _Types__Tag__t,
              );
            switch (Js.Dict.get(dict, "id")) {
            | None => Belt.Result.Error(["No attribute 'id'"])
            | Some(json) =>
              switch (
                (
                  string =>
                    switch (Js.Json.classify(string)) {
                    | JSONString(string) => Belt.Result.Ok(string)
                    | _ => Error(["expected a string"])
                    }
                )(
                  json,
                )
              ) {
              | Belt.Result.Error(error) =>
                Belt.Result.Error(["attribute 'id'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "name")) {
          | None => Belt.Result.Error(["No attribute 'name'"])
          | Some(json) =>
            switch (
              (
                string =>
                  switch (Js.Json.classify(string)) {
                  | JSONString(string) => Belt.Result.Ok(string)
                  | _ => Error(["expected a string"])
                  }
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'name'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "color")) {
        | None => Belt.Result.Error(["No attribute 'color'"])
        | Some(json) =>
          switch (
            (
              string =>
                switch (Js.Json.classify(string)) {
                | JSONString(string) => Belt.Result.Ok(string)
                | _ => Error(["expected a string"])
                }
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'color'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and serialize_Types____reference: _Types__reference => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("uri", Js.Json.string(record.uri)),
          (
            "start",
            {
              let (arg0, arg1) = record.start;
              Js.Json.array([|
                (int => Js.Json.number(float_of_int(int)))(arg0),
                (int => Js.Json.number(float_of_int(int)))(arg1),
              |]);
            },
          ),
          (
            "stop",
            {
              let (arg0, arg1) = record.stop;
              Js.Json.array([|
                (int => Js.Json.number(float_of_int(int)))(arg0),
                (int => Js.Json.number(float_of_int(int)))(arg1),
              |]);
            },
          ),
        |]),
      )
  and serialize_Types__Annotation__t: _Types__Annotation__t => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("id", Js.Json.string(record.id)),
          (
            "tags",
            Js.Json.array(
              Belt.List.toArray(Belt.List.map(record.tags, Js.Json.string)),
            ),
          ),
          (
            "references",
            Js.Json.array(
              Belt.List.toArray(
                Belt.List.map(
                  record.references,
                  serialize_Types____reference,
                ),
              ),
            ),
          ),
          ("notes", Js.Json.string(record.notes)),
          ("created", Js.Json.number(record.created)),
          ("modified", Js.Json.number(record.modified)),
        |]),
      )
  and serialize_Types__Tag__t: _Types__Tag__t => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("id", Js.Json.string(record.id)),
          ("name", Js.Json.string(record.name)),
          ("color", Js.Json.string(record.color)),
        |]),
      );
};
module Current = Version1;
let parseVersion = json =>
  switch (Js.Json.classify(json)) {
  | JSONObject(dict) =>
    switch (Js.Dict.get(dict, "$schemaVersion")) {
    | Some(schemaVersion) =>
      switch (Js.Json.classify(schemaVersion)) {
      | JSONNumber(version) =>
        [@implicit_arity] Belt.Result.Ok(int_of_float(version), json)
      | _ => Belt.Result.Error("Invalid $schemaVersion")
      }
    | None => Belt.Result.Error("No $schemaVersion present")
    }
  | JSONArray([|version, payload|]) =>
    switch (Js.Json.classify(version)) {
    | JSONNumber(version) =>
      [@implicit_arity] Belt.Result.Ok(int_of_float(version), payload)
    | _ => Belt.Result.Error("Invalid wrapped version")
    }
  | _ => Belt.Result.Error("Must have a schema version")
  };
let wrapWithVersion = (version, payload) =>
  switch (Js.Json.classify(payload)) {
  | JSONObject(dict) =>
    Js.Dict.set(
      dict,
      "$schemaVersion",
      Js.Json.number(float_of_int(version)),
    );
    Js.Json.object_(dict);
  | _ => Js.Json.array([|Js.Json.number(float_of_int(version)), payload|])
  };
let serializeAnnotation = data =>
  wrapWithVersion(
    currentVersion,
    Version1.serialize_Types__Annotation__t(data),
  )
and deserializeAnnotation = data =>
  switch (parseVersion(data)) {
  | Belt.Result.Error(err) => Belt.Result.Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 1 =>
      switch (Version1.deserialize_Types__Annotation__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) => Belt.Result.Ok(data)
      }
    | _ =>
      Belt.Result.Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
let serializeTag = data =>
  wrapWithVersion(currentVersion, Version1.serialize_Types__Tag__t(data))
and deserializeTag = data =>
  switch (parseVersion(data)) {
  | Belt.Result.Error(err) => Belt.Result.Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 1 =>
      switch (Version1.deserialize_Types__Tag__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) => Belt.Result.Ok(data)
      }
    | _ =>
      Belt.Result.Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
module Modules = {
  module Annotation = {
    type t = Types1._Types__Annotation__t;
    let serialize = serializeAnnotation;
    let deserialize = deserializeAnnotation;
  };
  module Tag = {
    type t = Types1._Types__Tag__t;
    let serialize = serializeTag;
    let deserialize = deserializeTag;
  };
};
