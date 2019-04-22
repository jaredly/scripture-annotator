
module Loading = {
  let let_ = (value, fn) => {
    switch value {
      | None => <div>{React.string("Loading...")}</div>
      | Some(v) => fn(v)
    }
  }
}

module App = {
  [@react.component]
  let make = () => {
    let (nav, setNav) = React.useReducer((_, action) => Some(action), None);
    React.useEffect0(() => {
      Content.nav |> Js.Promise.then_(result => {
        setNav(result);
        Js.Promise.resolve()
      }) |> ignore;
      None
    });
    let%Loading nav = nav;
    Js.log2("nav", nav);
    <div>
      {React.string("Hello")}
    </div>
  }
}

ReactDOMRe.renderToElementWithId(<App />, "root")
