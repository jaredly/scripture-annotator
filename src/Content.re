
let nav = {
  let%Lets.Async response = Web.fetch("/data/meta.json", Js.Obj.empty());
  response->Web.json
};
