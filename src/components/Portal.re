

[@react.component]
let make = (~children) => {
  let container = React.useRef(None);
  let container = switch (container->React.Ref.current) {
    | Some(node) => node
    | None =>
      let node = Web.document->Web.createElement("div");
      container->React.Ref.setCurrent(Some(node));
      Web.documentEl->Web.body->Web.appendChild(node);
      node
  };
  ReactDOMRe.createPortal(
    children,
    container
  )
};
