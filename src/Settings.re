type bookmark = {
  uri: string,
  scroll: float,
  date: float,
  name: string,
};

type settings = {
  lastUsedTags: list(string),
  history: array(bookmark),
  bookmarks: array(bookmark),
};