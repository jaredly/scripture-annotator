
let useState = (initial) => {
  React.useReducer((_, action) => action, initial);
};

module Loading = {
  let let_ = (value, fn) => {
    switch value {
      | None => <div>{React.string("Loading...")}</div>
      | Some(v) => fn(v)
    }
  }
}

let useHash = () => {
  let (hash, setHash) = useState(Web.Location.hash())
  React.useEffect0(() => {
    Some(Web.Location.addHashListener(setHash))
  });
  hash
};

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

let useNav = () => useLoading(() => Content.nav);

module App = {
  [@react.component]
  let make = () => {
    let hash = useHash();
    let%Loading nav = useNav();
    Js.log2("nav", nav);
    <div>
      <div>{React.string(hash)}</div>
      {
        nav->Js.Dict.values->Array.map(item => (
          <div key={item##uri} onClick={(_) => {
            Web.Location.setHash("#" ++ item##uri)
          }}>
            {React.string(item##title)}
          </div>
        ))->React.array
      }
      {React.string("Hello")}
    </div>
  }
};

ReactDOMRe.renderToElementWithId(<App />, "root")
