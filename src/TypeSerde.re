[@ocaml.warning "-34"];
module Types1 = {
  type _Settings__bookmark =
    Settings.bookmark = {
      uri: string,
      scroll: float,
      date: float,
      name: string,
    }
  and _Settings__settings =
    Settings.settings = {
      lastUsedTags: list(string),
      history: array(_Settings__bookmark),
      bookmarks: array(_Settings__bookmark),
    }
  and _Types__reference = {
    uri: string,
    start: (string, int),
    stop: (string, int),
    text: string,
  }
  and _Types__Annotation__t = {
    id: string,
    tags: list(string),
    references: list(_Types__reference),
    notes: string,
    created: float,
    modified: float,
  }
  and _Types__Tag__t = {
    id: string,
    name: string,
    color: string,
  };
};
module Types2 = {
  type _Belt_SetString__t = Belt_SetString.t
  and _Settings__bookmark =
    Settings.bookmark = {
      uri: string,
      scroll: float,
      date: float,
      name: string,
    }
  and _Settings__settings =
    Settings.settings = {
      lastUsedTags: list(string),
      history: array(_Settings__bookmark),
      bookmarks: array(_Settings__bookmark),
    }
  and _Types__reference =
    Types1._Types__reference = {
      uri: string,
      start: (string, int),
      stop: (string, int),
      text: string,
    }
  and _Types__Annotation__t = {
    id: string,
    study: string,
    tags: list(string),
    references: list(_Types__reference),
    notes: string,
    created: float,
    modified: float,
  }
  and _Types__Study__t =
    Types.Study.t = {
      id: string,
      title: string,
      created: float,
      finished: _Belt_SetString__t,
    }
  and _Types__Tag__t =
    Types.Tag.t = {
      id: string,
      study: string,
      name: string,
      color: string,
    };
  let rec migrate_Settings____bookmark:
    Types1._Settings__bookmark => _Settings__bookmark =
    _input_data => _input_data
  and migrate_Settings____settings:
    Types1._Settings__settings => _Settings__settings =
    _input_data => _input_data
  and migrate_Types____reference: Types1._Types__reference => _Types__reference =
    _input_data => _input_data
  and migrate_Types__Annotation__t:
    Types1._Types__Annotation__t => _Types__Annotation__t =
    _input_data => {
      let _converted_id = _input_data.id;
      let _converted_study =
        (a => "default": Types1._Types__Annotation__t => string)(_input_data);
      let _converted_tags = (Belt.List.map(_input_data.tags))(_item => _item);
      let _converted_references =
        (Belt.List.map(_input_data.references))(_item =>
          migrate_Types____reference(_item)
        );
      let _converted_notes = _input_data.notes;
      let _converted_created = _input_data.created;
      let _converted_modified = _input_data.modified;
      {
        modified: _converted_modified,
        created: _converted_created,
        notes: _converted_notes,
        references: _converted_references,
        tags: _converted_tags,
        study: _converted_study,
        id: _converted_id,
      };
    }
  and migrate_Types__Tag__t: Types1._Types__Tag__t => _Types__Tag__t =
    _input_data => {
      let _converted_id = _input_data.id;
      let _converted_study =
        (t => "default": Types1._Types__Tag__t => string)(_input_data);
      let _converted_name = _input_data.name;
      let _converted_color = _input_data.color;
      {
        color: _converted_color,
        name: _converted_name,
        study: _converted_study,
        id: _converted_id,
      };
    };
};
module Types3 = {
  type _Belt_SetString__t = Belt_SetString.t
  and _Settings__bookmark =
    Settings.bookmark = {
      uri: string,
      scroll: float,
      date: float,
      name: string,
    }
  and _Settings__settings =
    Settings.settings = {
      lastUsedTags: list(string),
      history: array(_Settings__bookmark),
      bookmarks: array(_Settings__bookmark),
    }
  and _Types__reference =
    Types.reference = {
      uri: string,
      start: (string, int),
      stop: (string, int),
      text: string,
      translation: string,
    }
  and _Types__Annotation__t =
    Types.Annotation.t = {
      id: string,
      study: string,
      tags: list(string),
      references: list(_Types__reference),
      notes: string,
      created: float,
      modified: float,
    }
  and _Types__Study__t =
    Types.Study.t = {
      id: string,
      title: string,
      created: float,
      finished: _Belt_SetString__t,
    }
  and _Types__Tag__t =
    Types.Tag.t = {
      id: string,
      study: string,
      name: string,
      color: string,
    };
  let rec migrate_Belt_SetString____t:
    Types2._Belt_SetString__t => _Belt_SetString__t =
    _input_data => _input_data
  and migrate_Settings____bookmark:
    Types2._Settings__bookmark => _Settings__bookmark =
    _input_data => _input_data
  and migrate_Settings____settings:
    Types2._Settings__settings => _Settings__settings =
    _input_data => _input_data
  and migrate_Types____reference: Types2._Types__reference => _Types__reference =
    _input_data => {
      let _converted_uri = _input_data.uri;
      let _converted_start = {
        let (arg0, arg1) = _input_data.start;
        (arg0, arg1);
      };
      let _converted_stop = {
        let (arg0, arg1) = _input_data.stop;
        (arg0, arg1);
      };
      let _converted_text = _input_data.text;
      let _converted_translation =
        (ref => "en-lds": Types2._Types__reference => string)(_input_data);
      {
        translation: _converted_translation,
        text: _converted_text,
        stop: _converted_stop,
        start: _converted_start,
        uri: _converted_uri,
      };
    }
  and migrate_Types__Annotation__t:
    Types2._Types__Annotation__t => _Types__Annotation__t =
    _input_data => {
      let _converted_id = _input_data.id;
      let _converted_study =
        (a => "default": Types2._Types__Annotation__t => string)(_input_data);
      let _converted_tags = (Belt.List.map(_input_data.tags))(_item => _item);
      let _converted_references =
        (Belt.List.map(_input_data.references))(_item =>
          migrate_Types____reference(_item)
        );
      let _converted_notes = _input_data.notes;
      let _converted_created = _input_data.created;
      let _converted_modified = _input_data.modified;
      {
        modified: _converted_modified,
        created: _converted_created,
        notes: _converted_notes,
        references: _converted_references,
        tags: _converted_tags,
        study: _converted_study,
        id: _converted_id,
      };
    }
  and migrate_Types__Study__t: Types2._Types__Study__t => _Types__Study__t =
    _input_data => _input_data
  and migrate_Types__Tag__t: Types2._Types__Tag__t => _Types__Tag__t =
    _input_data => _input_data;
};
let currentVersion = 3;
type target = Js.Json.t;
module Version1 = {
  open Types1;
  let rec deserialize_Settings____bookmark:
    target => Belt.Result.t(_Settings__bookmark, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_name => {
          let inner = attr_date => {
            let inner = attr_scroll => {
              let inner = attr_uri =>
                Belt.Result.Ok(
                  {
                    uri: attr_uri,
                    scroll: attr_scroll,
                    date: attr_date,
                    name: attr_name,
                  }: _Settings__bookmark,
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
            switch (Js.Dict.get(dict, "scroll")) {
            | None => Belt.Result.Error(["No attribute 'scroll'"])
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
                Belt.Result.Error(["attribute 'scroll'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "date")) {
          | None => Belt.Result.Error(["No attribute 'date'"])
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
              Belt.Result.Error(["attribute 'date'", ...error])
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
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Settings____settings:
    target => Belt.Result.t(_Settings__settings, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_bookmarks => {
          let inner = attr_history => {
            let inner = attr_lastUsedTags =>
              Belt.Result.Ok(
                {
                  lastUsedTags: attr_lastUsedTags,
                  history: attr_history,
                  bookmarks: attr_bookmarks,
                }: _Settings__settings,
              );
            switch (Js.Dict.get(dict, "lastUsedTags")) {
            | None => Belt.Result.Error(["No attribute 'lastUsedTags'"])
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
                        | [] => Belt.Result.Ok(Belt.List.reverse(collected))
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
                Belt.Result.Error(["attribute 'lastUsedTags'", ...error])
              | Ok(data) => inner(data)
              }
            };
          };
          switch (Js.Dict.get(dict, "history")) {
          | None => Belt.Result.Error(["No attribute 'history'"])
          | Some(json) =>
            switch (
              (
                (
                  (transformer, array) =>
                    switch (Js.Json.classify(array)) {
                    | JSONArray(items) =>
                      let rec loop = (i, collected, items) =>
                        switch (items) {
                        | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                        | [one, ...rest] =>
                          switch (transformer(one)) {
                          | Belt.Result.Error(error) =>
                            Belt.Result.Error([
                              "list element " ++ string_of_int(i),
                              ...error,
                            ])
                          | Ok(value) =>
                            loop(i + 1, [value, ...collected], rest)
                          }
                        };
                      switch (loop(0, [], Belt.List.fromArray(items))) {
                      | Belt.Result.Error(error) => Belt.Result.Error(error)
                      | Ok(value) => Ok(Belt.List.toArray(value))
                      };
                    | _ => Belt.Result.Error(["expected an array"])
                    }
                )(
                  deserialize_Settings____bookmark,
                )
              )(
                json,
              )
            ) {
            | Belt.Result.Error(error) =>
              Belt.Result.Error(["attribute 'history'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "bookmarks")) {
        | None => Belt.Result.Error(["No attribute 'bookmarks'"])
        | Some(json) =>
          switch (
            (
              (
                (transformer, array) =>
                  switch (Js.Json.classify(array)) {
                  | JSONArray(items) =>
                    let rec loop = (i, collected, items) =>
                      switch (items) {
                      | [] => Belt.Result.Ok(Belt.List.reverse(collected))
                      | [one, ...rest] =>
                        switch (transformer(one)) {
                        | Belt.Result.Error(error) =>
                          Belt.Result.Error([
                            "list element " ++ string_of_int(i),
                            ...error,
                          ])
                        | Ok(value) =>
                          loop(i + 1, [value, ...collected], rest)
                        }
                      };
                    switch (loop(0, [], Belt.List.fromArray(items))) {
                    | Belt.Result.Error(error) => Belt.Result.Error(error)
                    | Ok(value) => Ok(Belt.List.toArray(value))
                    };
                  | _ => Belt.Result.Error(["expected an array"])
                  }
              )(
                deserialize_Settings____bookmark,
              )
            )(
              json,
            )
          ) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'bookmarks'", ...error])
          | Ok(data) => inner(data)
          }
        };
      | _ => Belt.Result.Error(["Expected an object"])
      }
  and deserialize_Types____reference:
    target => Belt.Result.t(_Types__reference, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_text => {
          let inner = attr_stop => {
            let inner = attr_start => {
              let inner = attr_uri =>
                Belt.Result.Ok(
                  {
                    uri: attr_uri,
                    start: attr_start,
                    stop: attr_stop,
                    text: attr_text,
                  }: _Types__reference,
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
                            string =>
                              switch (Js.Json.classify(string)) {
                              | JSONString(string) => Belt.Result.Ok(string)
                              | _ => Error(["expected a string"])
                              }
                          )(
                            arg0,
                          )
                        ) {
                        | Belt.Result.Ok(arg0) =>
                          Belt.Result.Ok((arg0, arg1))
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
                          string =>
                            switch (Js.Json.classify(string)) {
                            | JSONString(string) => Belt.Result.Ok(string)
                            | _ => Error(["expected a string"])
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
        };
        switch (Js.Dict.get(dict, "text")) {
        | None => Belt.Result.Error(["No attribute 'text'"])
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
            Belt.Result.Error(["attribute 'text'", ...error])
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
      };
};
module Version2 = {
  open Types2;
  let rec deserialize_Belt_SetString____t:
    target => Belt.Result.t(_Belt_SetString__t, list(string)) = SerdeHelpers.deserialize_Belt_SetString____t
  and deserialize_Settings____bookmark:
    target => Belt.Result.t(_Settings__bookmark, list(string)) = Version1.deserialize_Settings____bookmark
  and deserialize_Settings____settings:
    target => Belt.Result.t(_Settings__settings, list(string)) = Version1.deserialize_Settings____settings
  and deserialize_Types____reference:
    target => Belt.Result.t(_Types__reference, list(string)) = Version1.deserialize_Types____reference
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
                  let inner = attr_study => {
                    let inner = attr_id =>
                      Belt.Result.Ok(
                        {
                          id: attr_id,
                          study: attr_study,
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
                  switch (Js.Dict.get(dict, "study")) {
                  | None => Belt.Result.Error(["No attribute 'study'"])
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
                      Belt.Result.Error(["attribute 'study'", ...error])
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
  and deserialize_Types__Study__t:
    target => Belt.Result.t(_Types__Study__t, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_finished => {
          let inner = attr_created => {
            let inner = attr_title => {
              let inner = attr_id =>
                Belt.Result.Ok(
                  {
                    id: attr_id,
                    title: attr_title,
                    created: attr_created,
                    finished: attr_finished,
                  }: _Types__Study__t,
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
            switch (Js.Dict.get(dict, "title")) {
            | None => Belt.Result.Error(["No attribute 'title'"])
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
                Belt.Result.Error(["attribute 'title'", ...error])
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
        switch (Js.Dict.get(dict, "finished")) {
        | None => Belt.Result.Error(["No attribute 'finished'"])
        | Some(json) =>
          switch (deserialize_Belt_SetString____t(json)) {
          | Belt.Result.Error(error) =>
            Belt.Result.Error(["attribute 'finished'", ...error])
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
            let inner = attr_study => {
              let inner = attr_id =>
                Belt.Result.Ok(
                  {
                    id: attr_id,
                    study: attr_study,
                    name: attr_name,
                    color: attr_color,
                  }: _Types__Tag__t,
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
            switch (Js.Dict.get(dict, "study")) {
            | None => Belt.Result.Error(["No attribute 'study'"])
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
                Belt.Result.Error(["attribute 'study'", ...error])
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
      };
};
module Version3 = {
  open Types3;
  let rec deserialize_Belt_SetString____t:
    target => Belt.Result.t(_Belt_SetString__t, list(string)) = Version2.deserialize_Belt_SetString____t
  and deserialize_Settings____bookmark:
    target => Belt.Result.t(_Settings__bookmark, list(string)) = Version2.deserialize_Settings____bookmark
  and deserialize_Settings____settings:
    target => Belt.Result.t(_Settings__settings, list(string)) = Version2.deserialize_Settings____settings
  and deserialize_Types____reference:
    target => Belt.Result.t(_Types__reference, list(string)) =
    record =>
      switch (Js.Json.classify(record)) {
      | JSONObject(dict) =>
        let inner = attr_translation => {
          let inner = attr_text => {
            let inner = attr_stop => {
              let inner = attr_start => {
                let inner = attr_uri =>
                  Belt.Result.Ok(
                    {
                      uri: attr_uri,
                      start: attr_start,
                      stop: attr_stop,
                      text: attr_text,
                      translation: attr_translation,
                    }: _Types__reference,
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
                              string =>
                                switch (Js.Json.classify(string)) {
                                | JSONString(string) =>
                                  Belt.Result.Ok(string)
                                | _ => Error(["expected a string"])
                                }
                            )(
                              arg0,
                            )
                          ) {
                          | Belt.Result.Ok(arg0) =>
                            Belt.Result.Ok((arg0, arg1))
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
                            string =>
                              switch (Js.Json.classify(string)) {
                              | JSONString(string) => Belt.Result.Ok(string)
                              | _ => Error(["expected a string"])
                              }
                          )(
                            arg0,
                          )
                        ) {
                        | Belt.Result.Ok(arg0) =>
                          Belt.Result.Ok((arg0, arg1))
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
          };
          switch (Js.Dict.get(dict, "text")) {
          | None => Belt.Result.Error(["No attribute 'text'"])
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
              Belt.Result.Error(["attribute 'text'", ...error])
            | Ok(data) => inner(data)
            }
          };
        };
        switch (Js.Dict.get(dict, "translation")) {
        | None => Belt.Result.Error(["No attribute 'translation'"])
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
            Belt.Result.Error(["attribute 'translation'", ...error])
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
                  let inner = attr_study => {
                    let inner = attr_id =>
                      Belt.Result.Ok(
                        {
                          id: attr_id,
                          study: attr_study,
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
                  switch (Js.Dict.get(dict, "study")) {
                  | None => Belt.Result.Error(["No attribute 'study'"])
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
                      Belt.Result.Error(["attribute 'study'", ...error])
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
  and deserialize_Types__Study__t:
    target => Belt.Result.t(_Types__Study__t, list(string)) = Version2.deserialize_Types__Study__t
  and deserialize_Types__Tag__t:
    target => Belt.Result.t(_Types__Tag__t, list(string)) = Version2.deserialize_Types__Tag__t
  and serialize_Belt_SetString____t: _Belt_SetString__t => target = SerdeHelpers.serialize_Belt_SetString____t
  and serialize_Settings____bookmark: _Settings__bookmark => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("uri", Js.Json.string(record.uri)),
          ("scroll", Js.Json.number(record.scroll)),
          ("date", Js.Json.number(record.date)),
          ("name", Js.Json.string(record.name)),
        |]),
      )
  and serialize_Settings____settings: _Settings__settings => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          (
            "lastUsedTags",
            Js.Json.array(
              Belt.List.toArray(
                Belt.List.map(record.lastUsedTags, Js.Json.string),
              ),
            ),
          ),
          (
            "history",
            (
              (
                (transformer, array) =>
                  Js.Json.array((Belt.Array.map(array))(transformer))
              )(
                serialize_Settings____bookmark,
              )
            )(
              record.history,
            ),
          ),
          (
            "bookmarks",
            (
              (
                (transformer, array) =>
                  Js.Json.array((Belt.Array.map(array))(transformer))
              )(
                serialize_Settings____bookmark,
              )
            )(
              record.bookmarks,
            ),
          ),
        |]),
      )
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
                Js.Json.string(arg0),
                (int => Js.Json.number(float_of_int(int)))(arg1),
              |]);
            },
          ),
          (
            "stop",
            {
              let (arg0, arg1) = record.stop;
              Js.Json.array([|
                Js.Json.string(arg0),
                (int => Js.Json.number(float_of_int(int)))(arg1),
              |]);
            },
          ),
          ("text", Js.Json.string(record.text)),
          ("translation", Js.Json.string(record.translation)),
        |]),
      )
  and serialize_Types__Annotation__t: _Types__Annotation__t => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("id", Js.Json.string(record.id)),
          ("study", Js.Json.string(record.study)),
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
  and serialize_Types__Study__t: _Types__Study__t => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("id", Js.Json.string(record.id)),
          ("title", Js.Json.string(record.title)),
          ("created", Js.Json.number(record.created)),
          ("finished", serialize_Belt_SetString____t(record.finished)),
        |]),
      )
  and serialize_Types__Tag__t: _Types__Tag__t => target =
    record =>
      Js.Json.object_(
        Js.Dict.fromArray([|
          ("id", Js.Json.string(record.id)),
          ("study", Js.Json.string(record.study)),
          ("name", Js.Json.string(record.name)),
          ("color", Js.Json.string(record.color)),
        |]),
      );
};
module Current = Version3;
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
let serializeSettings = data =>
  wrapWithVersion(
    currentVersion,
    Version3.serialize_Settings____settings(data),
  )
and deserializeSettings = data =>
  switch (parseVersion(data)) {
  | Belt.Result.Error(err) => Belt.Result.Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 3 =>
      switch (Version3.deserialize_Settings____settings(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) => Belt.Result.Ok(data)
      }
    | 2 =>
      switch (Version2.deserialize_Settings____settings(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types3.migrate_Settings____settings(data);
        Belt.Result.Ok(data);
      }
    | 1 =>
      switch (Version1.deserialize_Settings____settings(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types2.migrate_Settings____settings(data);
        let data = Types3.migrate_Settings____settings(data);
        Belt.Result.Ok(data);
      }
    | _ =>
      Belt.Result.Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
let serializeStudy = data =>
  wrapWithVersion(currentVersion, Version3.serialize_Types__Study__t(data))
and deserializeStudy = data =>
  switch (parseVersion(data)) {
  | Belt.Result.Error(err) => Belt.Result.Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 3 =>
      switch (Version3.deserialize_Types__Study__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) => Belt.Result.Ok(data)
      }
    | 2 =>
      switch (Version2.deserialize_Types__Study__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types3.migrate_Types__Study__t(data);
        Belt.Result.Ok(data);
      }
    | _ =>
      Belt.Result.Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
let serializeAnnotation = data =>
  wrapWithVersion(
    currentVersion,
    Version3.serialize_Types__Annotation__t(data),
  )
and deserializeAnnotation = data =>
  switch (parseVersion(data)) {
  | Belt.Result.Error(err) => Belt.Result.Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 3 =>
      switch (Version3.deserialize_Types__Annotation__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) => Belt.Result.Ok(data)
      }
    | 2 =>
      switch (Version2.deserialize_Types__Annotation__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types3.migrate_Types__Annotation__t(data);
        Belt.Result.Ok(data);
      }
    | 1 =>
      switch (Version1.deserialize_Types__Annotation__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types2.migrate_Types__Annotation__t(data);
        let data = Types3.migrate_Types__Annotation__t(data);
        Belt.Result.Ok(data);
      }
    | _ =>
      Belt.Result.Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
let serializeTag = data =>
  wrapWithVersion(currentVersion, Version3.serialize_Types__Tag__t(data))
and deserializeTag = data =>
  switch (parseVersion(data)) {
  | Belt.Result.Error(err) => Belt.Result.Error([err])
  | [@implicit_arity] Ok(version, data) =>
    switch (version) {
    | 3 =>
      switch (Version3.deserialize_Types__Tag__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) => Belt.Result.Ok(data)
      }
    | 2 =>
      switch (Version2.deserialize_Types__Tag__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types3.migrate_Types__Tag__t(data);
        Belt.Result.Ok(data);
      }
    | 1 =>
      switch (Version1.deserialize_Types__Tag__t(data)) {
      | Belt.Result.Error(error) => Belt.Result.Error(error)
      | Ok(data) =>
        let data = Types2.migrate_Types__Tag__t(data);
        let data = Types3.migrate_Types__Tag__t(data);
        Belt.Result.Ok(data);
      }
    | _ =>
      Belt.Result.Error(["Unexpected version " ++ string_of_int(version)])
    }
  };
module Modules = {
  module Settings = {
    type t = Types3._Settings__settings;
    let serialize = serializeSettings;
    let deserialize = deserializeSettings;
  };
  module Study = {
    type t = Types3._Types__Study__t;
    let serialize = serializeStudy;
    let deserialize = deserializeStudy;
  };
  module Annotation = {
    type t = Types3._Types__Annotation__t;
    let serialize = serializeAnnotation;
    let deserialize = deserializeAnnotation;
  };
  module Tag = {
    type t = Types3._Types__Tag__t;
    let serialize = serializeTag;
    let deserialize = deserializeTag;
  };
};