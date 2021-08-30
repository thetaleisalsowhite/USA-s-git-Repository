'use strict';

chrome.runtime.onInstalled.addListener(function() {
  var parent = chrome.contextMenus.create({
    id: 'parent',
    title: 'Choose Background Color'
  });
  chrome.contextMenus.create({
    id: 'red',
    parentId: parent,
    title: 'Red'
  });
  chrome.contextMenus.create({
    id: 'blue',
    parentId: parent,
    title: 'Blue'
  });
  chrome.contextMenus.create({
    id: 'green',
    parentId: parent,
    title: 'Green'
  });
});

chrome.contextMenus.onClicked.addListener(function(item) {
  chrome.tabs.executeScript({
    code: 'document.body.style.backgroundColor = "' + item.menuItemId + '"'
  });
});