let reduce = (state: Types.state, action) => switch action {
  | `AddAnnotation(annotation: Types.Annotation.t) => {
    Database.setItem(Database.annotationDb, annotation.id, annotation)->ignore;
    {...state, Types.annotations: state.annotations->Map.String.set(annotation.id, annotation)}
  }
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
      onSave={annotation => dispatch(`AddAnnotation(annotation))}
    />
  </div>;
};
