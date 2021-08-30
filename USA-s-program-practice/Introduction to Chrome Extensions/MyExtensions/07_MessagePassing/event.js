'use strict';

chrome.runtime.onMessage.addListener(
  function(message, sender, callback) {
    chrome.browserAction.setBadgeText({text: message.count + ''});
  }
);