
[@react.component]
let make = (~children, ~onClose) => {
  <Portal>
    <div
      className=Css.(
        style([
          position(`fixed),
          top(`zero),
          left(`zero),
          bottom(`zero),
          right(`zero),
          justifyContent(`center),
          alignItems(`center),
          backgroundColor(rgba(0, 0, 0, 0.1)),
        ])
      )
      onClick={evt => onClose()}>
      <div
        onClick={evt => {
          evt->ReactEvent.Mouse.stopPropagation;
        }}
      >
        {children}
      </div>
    </div>
  </Portal>;
};