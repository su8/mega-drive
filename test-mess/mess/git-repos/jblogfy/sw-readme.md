sw.js is the short-hand name for ServiceWorker, which is used to cache the index.html, blog and post engines residing in this folder.

Whenever you change something in the **dev** folder, make sure to open the sw.js and update the 'expectedCache' value so it points to newer cache version which the blog visitor browser will know and sync the newer cache.

It's useful because your blog visitors will be able to use the blog app as well visit your blog page without having access to internet (offline).
