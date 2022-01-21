'use strict';

document.getElementById('colors').addEventListener('change', function() {
  chrome.tabs.executeScript({
    code: 'document.body.style.backgroundColor = "' + this.value + '"'
  });
});