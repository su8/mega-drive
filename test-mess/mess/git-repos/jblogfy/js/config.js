(function(w) {
    'use strict';

    var metaPool = [
        ["sane_gentoo_commands","Sane Gentoo Commands","May 7, 2016","Gentoo"],
        ["hello_world","Oh Hello !","May 24, 2016",""]

    ];

    w.metaPool = Object.freeze(metaPool);

    if ('serviceWorker' in navigator) {
      if (!!navigator.serviceWorker.controller) {
        navigator.serviceWorker.controller.postMessage(JSON.stringify(metaPool));
      }
    }
}(window));
