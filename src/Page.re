let reduce = (state: Types.state, action) =>
  switch (action) {
  | `Reset(state) => state
  | `Save =>
    let current = state.current->Types.Annotation.prepare;
    Database.setItem(Database.annotationDb, current.id, current)->ignore;
    {
      ...state,
      current,
      Types.annotations:
        state.annotations->Map.String.set(current.id, current),
    };
  | `Clear => {...state, current: state.current->Types.Annotation.clear}
  | `Delete =>
    Database.removeItem(Database.annotationDb, state.current.id)->ignore;
    {
      ...state,
      current: state.current->Types.Annotation.clear,
      annotations: state.annotations->Map.String.remove(state.current.id),
    };
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
  | `ChangeTag((tag: Types.Tag.t)) =>
    Database.tagsDb->Database.setItem(tag.id, tag)->ignore;
    {...state, tags: state.tags->Map.String.set(tag.id, tag)};
  | `AddTag(id) => {
      ...state,
      current: {
        ...state.current,
        tags: state.current.tags->List.keep(t => t != id)->List.concat([id]),
      },
    }
  | `CreateTag(name) =>
    let tag = Types.Tag.create(~name, ~color="#afa", ~study="default");
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

let positionAnnotations =
    (~node, ~container, ~annotations, ~current: Types.Annotation.t, ~uri) => {
  let offset = container->Web.getBoundingClientRect;
  annotations
  ->Map.String.set(current.id, current)
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
            let%Lets.Opt () = ref.uri == uri ? Some() : None;
            let%Lets.Opt rect = positionReference(ref);
            // Js.log2(ref, rect);
            Some((rect##top -. offset##top, rect##height, ref));
          });
      relevant == [||] ? None : Some((ann, relevant));
    });
};

[@react.component]
let make = (~meta, ~volume as _, ~content, ~state: Types.state, ~dispatch) => {
  let (node, setNode) = Hooks.useState(None);
  let annotationContainer = React.useRef(Js.Nullable.null);
  let (delayedMeta, setDelayedMeta) = Hooks.useState(meta);
  React.useLayoutEffect1(
    () => {
      Js.Global.setTimeout(() => setDelayedMeta(meta), 50)->ignore;
      None;
    },
    [|meta|],
  );
  let positionedAnnotations =
    React.useMemo4(
      () =>
        switch (
          node,
          annotationContainer->React.Ref.current->Js.Nullable.toOption,
        ) {
        | (None, _)
        | (_, None) => [||]
        | (Some(node), Some(container)) =>
          positionAnnotations(
            ~node,
            ~container,
            ~annotations=state.annotations,
            ~current=state.current,
            ~uri=delayedMeta##uri,
          )
        },
      (node, state.annotations, state.current, delayedMeta),
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
              translation: "en-lds",
              start,
              stop,
              text: s->Web.Selection.getRange->Web.Range.toHTML,
            },
          ],
      }),
    );
  };
  <div
    className=Css.(
      style([flex(1), flexDirection(`row), justifyContent(`center)])
    )>
    <div
      className=Css.(
        style([
          overflow(`auto),
          flexShrink(0),
          position(`relative),
          flexDirection(`row),
        ])
      )
      tabIndex=(-1)
      onKeyDown={evt =>
        switch (ReactEvent.Keyboard.key(evt)) {
        | "Enter" => addSelection(evt->ReactEvent.Keyboard.shiftKey)
        | "Escape" =>
          dispatch(`Clear);
          Web.Selection.current()->Web.Selection.removeAllRanges;
        | _ => ()
        }
      }>
      <div
        key={meta##uri}
        className=Css.(
          style([
            // focus([
            //   outlineStyle(`none)
            // ]),
            width(px(400)),
            padding(px(32)),
            selector(
              " > :last-child",
              [marginBottom(px(400)), flexShrink(0)],
            ),
          ])
        )
        onMouseDown={evt =>
          if (ReactEvent.Mouse.metaKey(evt)) {
            addSelection(false);
          }
        }
        dangerouslySetInnerHTML={"__html": content##content}
        ref={ReactDOMRe.Ref.callbackDomRef(node
          // Js.log2("Setting ref", node);
          => setNode(node->Js.Nullable.toOption))}
      />
      <ReferencesView
        containerRef=annotationContainer
        state
        dispatch
        positionedAnnotations
      />
    </div>
    <AnnotationEditor
      state
      uri={meta##uri}
      addSelection
      onChange={annotation => dispatch(`Update(annotation))}
      onClear={annotation => dispatch(`Clear)}
      onDelete={annotation => dispatch(`Delete)}
      onSave={annotation => dispatch(`Save)}
      onAddTag={id => dispatch(`AddTag(id))}
      onChangeTag={tag => dispatch(`ChangeTag(tag))}
      onCreateTag={name => dispatch(`CreateTag(name))}
      onRemoveTag={name => dispatch(`RemoveTag(name))}
    />
  </div>;
};