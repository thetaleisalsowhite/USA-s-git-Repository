'use strict';

document.addEventListener('DOMContentLoaded', function() {
  chrome.storage.sync.get({
    color: 'red'
  }, function(item) {
    document.getElementById('colors').value = item.color;
  });
});

document.getElementById('save').addEventListener('click', function() {
  var color = document.getElementById('colors').value;
  chrome.storage.sync.set({
    color: color
  }, function() {
    console.log('saved: ' + color);
  });
});

// document.getElementById('colors').addEventListener('change', function() {
//   chrome.tabs.executeScript({
//     code: 'document.body.style.backgroundColor = "' + this.value + '"'
//   });
// });