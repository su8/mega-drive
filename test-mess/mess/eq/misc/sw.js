/*
 Copyright 2014 Google Inc. All Rights Reserved.
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

/* Port to es6 when most browsers support native es6
   Mobile debugging chrome://serviceworker-internals/ */

/* The console.logs are here to make the mobile
 * debugging easier, since the mobile browser versions
 * does not have access to the developer tools */

var needsUpdate = true;
var expectedCache = '7.0.0.14';
var filesToCache = [
    './index.html',
    './js/blog-engine.min.js',
    './js/post-engine.min.js',
    './img/icons/icon.ico',
    './manifest.json'
];

function writeToNewCache() {
  if (needsUpdate && navigator.onLine) {
    console.log('Write new cache ' + expectedCache);
      caches.open(expectedCache).then(function(cache) {
        return cache.addAll(filesToCache);
      });
  }
}

function checkCache(event) {
  event.waitUntil(
    caches.keys().then(function(cacheNames) {
      return Promise.all([
        cacheNames.map(function(cacheName) {
            console.log('in first promise');
          if (cacheName === expectedCache) {
            needsUpdate = false;
            console.log('up-to-date ' + cacheName);
          } else {
            console.log('Deleting ' + cacheName);
            caches.delete(cacheName);
          }
        }),
        writeToNewCache()
      ]);
    })
  );
}

self.addEventListener('install', function() {
    console.log('Hello active');
});
self.addEventListener('activate', checkCache);

self.addEventListener('fetch', function(event) {
  event.respondWith(
    caches.match(event.request).then(function(response) {
      return (response || fetch(event.request));
    }).catch(function(error) {
      console.log('oh snap!');
      throw error;
    })
  );
});
