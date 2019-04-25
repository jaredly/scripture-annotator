[@react.component]
let make = (~value as initial, ~onChange, ~className=?) => {
  let (value, setValue) = Hooks.useState(initial);
  Hooks.useFromProps(initial, newValue => setValue(newValue));
  <textarea
    value
    ?className
    onChange={evt => setValue(evt->ReactEvent.Form.target##value)}
    onBlur={evt => onChange(value)}
  />;
};
