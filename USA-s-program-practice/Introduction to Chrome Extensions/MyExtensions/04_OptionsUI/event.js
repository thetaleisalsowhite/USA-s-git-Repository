'use strict';

chrome.browserAction.onClicked.addListener(function() {
  chrome.storage.sync.get({
    color: 'red'
  }, function(item) {
    chrome.tabs.executeScript({
      code: 'document.body.style.backgroundColor = "' + item.color + '"'
    });
  });
});