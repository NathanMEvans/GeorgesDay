
mergeInto(LibraryManager.library, {
    js_getScreenWidth: function()  {
        var w = Module.textAreaWidth();
        return w;
    },
    js_getScreenHeight: function()  {
        var h = window.innerHeight/8;
        return h;
    }
  });
