
let reduce = (state: Types.state, action) => switch action {
  | `Save => {
    let current = state.current->Types.Annotation.prepare;
    Database.setItem(Database.annotationDb, current.id, current)->ignore;
    {...state, current, Types.annotations: state.annotations->Map.String.set(current.id, current)}
  }
  | `Clear => {...state, current: state.current->Types.Annotation.clear}
  | `Update(current) => {...state, current}
};

[@react.component]
let make = (~meta, ~volume, ~content, ~state) => {
  let (state, dispatch) = React.useReducer(reduce, state);
  let (node, setNode) = Hooks.useState(None);
  let positionedAnnotations = React.useMemo3(() => {
    if (node == None) {
      [||]
    } else {
      // state.annotations->Map.String.valuesToArray->Array.map(ann => {
        state.current.references->List.toArray->Array.keepMap(ref => {
          let%Lets.Opt () = ref.uri == meta##uri ? Some(()) : None
          let%Lets.Opt start = Web.Selection.fromSingleIdOffset(ref.start);
          let%Lets.Opt stop = Web.Selection.fromSingleIdOffset(ref.stop);
          let range = Web.Range.createRange();
          range->Web.Range.setStart(start);
          range->Web.Range.setEnd(stop);
          let rect = range->Web.Range.getBoundingClientRect;
          Some((rect##top, rect##height, ref, state.current))
        })
      // })->Array.concatMany
    }
  }, (node, state.annotations, state.current));

  let addSelection = () => {
    let s = Web.Selection.current();
    let%Lets.OptConsume (start, stop) = s->Web.Selection.toIdOffset;
    dispatch(`Update({
      ...state.current,
      references: state.current.references @ [{
        uri: meta##uri,
        start,
        stop,
        text: s->Web.Selection.toString,
      }]
    }))
  };
  <div className=Css.(style([
    flexDirection(`row)
  ]))>
    <div
      tabIndex={-1}
      className=Css.(style([
        width(px(400)),
        flexShrink(0)
      ]))
      onMouseDown={evt => {
        if (ReactEvent.Mouse.metaKey(evt)) {
          addSelection()
        }
      }}
      onKeyDown={evt => {
        if (ReactEvent.Keyboard.key(evt) == "Enter") {
          addSelection();
        // } else {
        //   Js.log(evt)
        }
      }}
      dangerouslySetInnerHTML={"__html": content##content}
      ref={ReactDOMRe.Ref.callbackDomRef(node =>
        setNode(node->Js.Nullable.toOption)
      )}
    />
    <div className=Css.(style([
      width(px(50))
    ]))>
      {positionedAnnotations->Array.mapWithIndex((i, (top, height, ref, ann)) => (
        <div
          key=Js.Int.toString(i)
          style={ReactDOMRe.Style.make(
            ~top=Js.Float.toString(top) ++ "px",
            // ~marginLeft=Js.Int.toString(i * 5) ++ "px",
            ~height=Js.Float.toString(height) ++ "px",
            ~backgroundColor="red",
            ~opacity="0.3",
            ~width="4px",
            ~position="absolute",
            ()
          )}
        />
      ))->React.array}
    </div>
    <AnnotationEditor
      state
      uri={meta##uri}
      onChange={annotation => dispatch(`Update(annotation))}
      onClear={annotation => dispatch(`Clear)}
      onSave={annotation => dispatch(`Save)}
    />
  </div>;
};
