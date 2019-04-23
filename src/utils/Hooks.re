
let useState = (initial) => {
  React.useReducer((_, action) => action, initial);
};

let useHash = () => {
  let (hash, setHash) = useState(Web.Location.hash())
  React.useEffect0(() => {
    Some(Web.Location.addHashListener(setHash))
  });
  hash
};

let useFromProps = (currentProp, onChange) => {
  let prevValue = React.useRef(currentProp);
  if (prevValue->React.Ref.current != currentProp) {
    prevValue->React.Ref.setCurrent(currentProp);
    onChange(currentProp);
  };
}

let useLoading = getter => {
  let (nav, setNav) = useState(None);
  React.useEffect0(() => {
    getter() |> Js.Promise.then_(result => {
      setNav(Some(result));
      Js.Promise.resolve()
    }) |> ignore;
    None
  });
  nav
};
