
[@react.component]
let make = (~value as initial, ~onChange) => {
  let (value, setValue) = Hooks.useState(initial);
  Hooks.useFromProps(initial, newValue => setValue(newValue));
  <input
    value
    onChange={evt => setValue(evt->ReactEvent.Form.target##value)}
    onBlur={evt => onChange(value)}
  />;
};
