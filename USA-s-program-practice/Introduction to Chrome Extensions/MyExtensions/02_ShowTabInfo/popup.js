'use strict';

chrome.tabs.query({}, function(tabs) {
  var i;
  for (i = 0; i < tabs.length; i++) {
    console.log(tabs[i].title);
  }
});