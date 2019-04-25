let reduce = (state: Types.state, action) =>
  switch (action) {
  | `Save =>
    let current = state.current->Types.Annotation.prepare;
    Database.setItem(Database.annotationDb, current.id, current)->ignore;
    {
      ...state,
      current: current->Types.Annotation.clear,
      Types.annotations:
        state.annotations->Map.String.set(current.id, current),
    };
  | `Clear => {...state, current: state.current->Types.Annotation.clear}
  | `Update(current) => {...state, current}
  | `Select(id) =>
    switch (state.annotations->Map.String.get(id)) {
    | None => state
    | Some(current) => {...state, current}
    }
  | `RemoveTag(id) => {
      ...state,
      current: {
        ...state.current,
        tags: state.current.tags->List.keep(t => t != id),
      },
    }
  | `AddTag(id) => {
      ...state,
      current: {
        ...state.current,
        tags: state.current.tags->List.keep(t => t != id)->List.concat([id]),
      },
    }
  | `CreateTag(name) =>
    let tag = Types.Tag.create(~name, ~color="#afa");
    Database.tagsDb->Database.setItem(tag.id, tag)->ignore;
    {
      ...state,
      tags: state.tags->Map.String.set(tag.id, tag),
      current: {
        ...state.current,
        tags:
          state.current.tags
          ->List.keep(t => t != tag.id)
          ->List.concat([tag.id]),
      },
    };
  };

let positionReference = (ref: Types.reference) => {
  let%Lets.Opt start = Web.Selection.fromSingleIdOffset(ref.start);
  let%Lets.Opt stop = Web.Selection.fromSingleIdOffset(ref.stop);
  let range = Web.Range.createRange();
  range->Web.Range.setStart(start);
  range->Web.Range.setEnd(stop);
  let rect = range->Web.Range.getBoundingClientRect;
  Some(rect);
};

[@react.component]
let make = (~meta, ~volume, ~content, ~state) => {
  let (state, dispatch) = React.useReducer(reduce, state);
  let (node, setNode) = Hooks.useState(None);
  let positionedAnnotations =
    React.useMemo3(
      () =>
        if (node == None) {
          [||];
        } else {
          state.annotations
          ->Map.String.set(state.current.id, state.current)
          ->Map.String.valuesToArray
          ->Js.Array.sortInPlaceWith(
              (a: Types.Annotation.t, b) => compare(a.id, b.id),
              _,
            )
          ->Array.keepMap(ann => {
              let relevant =
                ann.references
                ->List.toArray
                ->Array.keepMap(ref => {
                    let%Lets.Opt () = ref.uri == meta##uri ? Some() : None;
                    let%Lets.Opt rect = positionReference(ref);
                    Js.log2(ref, rect);
                    Some((rect##top, rect##height, ref));
                  });
              relevant == [||] ? None : Some((ann, relevant));
            });
        },
      (node, state.annotations, state.current),
    );

  let addSelection = fullVerses => {
    let s = Web.Selection.current();
    let%Lets.OptConsume (start, stop) =
      s->Web.Selection.toIdOffset(fullVerses);
    dispatch(
      `Update({
        ...state.current,
        references:
          state.current.references
          @ [
            {
              uri: meta##uri,
              start,
              stop,
              text: s->Web.Selection.getRange->Web.Range.toHTML,
            },
          ],
      }),
    );
  };
  <div className=Css.(style([flexDirection(`row)]))>
    <div
      tabIndex=(-1)
      className=Css.(style([width(px(400)), flexShrink(0)]))
      onMouseDown={evt =>
        if (ReactEvent.Mouse.metaKey(evt)) {
          addSelection(false);
        }
      }
      onKeyDown={evt =>
        if (ReactEvent.Keyboard.key(evt) == "Enter") {
          addSelection(evt->ReactEvent.Keyboard.shiftKey);
        }
      }
      dangerouslySetInnerHTML={"__html": content##content}
      ref={ReactDOMRe.Ref.callbackDomRef(node =>
        setNode(node->Js.Nullable.toOption)
      )}
    />
    <div
      className=Css.(
        style([
          minWidth(px(50)),
          marginLeft(px(10)),
          flexDirection(`row),
        ])
      )>
      {positionedAnnotations
       ->Array.mapWithIndex((i, (ann, references)) =>
           <div
             onClick={evt => dispatch(`Select(ann.id))}
             key={string_of_int(i)}
             className=Css.(
               style([
                 width(px(10)),
                 cursor(`pointer),
                 hover([
                   selector(" > div", [outline(px(1), `solid, black)]),
                 ]),
               ])
             )>
             {references
              ->Array.mapWithIndex((i, (top, height, ref)) =>
                  <div
                    key={Js.Int.toString(i)}
                    className=Css.(
                      style([
                        backgroundColor(rgba(255, 0, 0, 0.3)),
                        width(px(10)),
                        position(`absolute),
                      ])
                    )
                    style={ReactDOMRe.Style.make(
                      ~top=Js.Float.toString(top) ++ "px",
                      // ~marginLeft=Js.Int.toString(i * 5) ++ "px",
                      ~height=Js.Float.toString(height) ++ "px",
                      ~outline=
                        ann.id == state.current.id ? "1px solid black" : "",
                      (),
                    )}
                  />
                )
              ->React.array}
           </div>
         )
       ->React.array}
    </div>
    <AnnotationEditor
      state
      uri={meta##uri}
      addSelection
      onChange={annotation => dispatch(`Update(annotation))}
      onClear={annotation => dispatch(`Clear)}
      onSave={annotation => dispatch(`Save)}
      onAddTag={id => dispatch(`AddTag(id))}
      onCreateTag={name => dispatch(`CreateTag(name))}
      onRemoveTag={name => dispatch(`RemoveTag(name))}
    />
  </div>;
};