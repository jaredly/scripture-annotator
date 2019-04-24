
[@react.component]
let make = (~tags: Map.String.t(Types.Tag.t), ~current, ~onCreate, ~onAdd, ~onRemove) => {
  let (newText, setNewText) = Hooks.useState("");
  <div>
    {React.string("Current Tags")}
    {current->List.toArray->Array.keepMap(id => {
      let%Lets.OptWrap tag = tags->Map.String.get(id);
      <div id=tag.id>
        {React.string(tag.name)}
      </div>
    })->React.array}
    <input
      value=newText
      onChange={evt => {
        let text = evt->ReactEvent.Form.target##value;
        setNewText(text)
      }}
    />
    <button onClick={evt => {
      if (newText != "") {
        onCreate(newText)
      }
    }}
    >
      {React.string("Create")}
    </button>
    {React.string("All tags")}
    {tags->Map.String.valuesToArray->Array.map(tag => (
      <button
        key={tag.id}
        onClick={evt => onAdd(tag.id)}
      >
        {React.string(tag.name)}
      </button>
    ))->React.array}
  </div>
};
