
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
  <div className=Css.(style([
    flexDirection(`row)
  ]))>
    <div
      className=Css.(style([
        maxWidth(px(400))
      ]))
      dangerouslySetInnerHTML={"__html": content##content}
      ref={ReactDOMRe.Ref.callbackDomRef(node =>
        setNode(node->Js.Nullable.toOption)
      )}
    />
    <div />
    <AnnotationEditor
      state
      uri={meta##uri}
      onChange={annotation => dispatch(`Update(annotation))}
      onClear={annotation => dispatch(`Clear)}
      onSave={annotation => dispatch(`Save)}
    />
  </div>;
};
