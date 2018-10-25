// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

'use strict';

//获取按钮元素
let changeColor = document.getElementById('changeColor');
//获取coler的值，设置按钮元素的样式
chrome.storage.sync.get('color', function(data) {
  changeColor.style.backgroundColor = data.color;
  changeColor.setAttribute('value', data.color);
});

//为按钮绑定click事件
changeColor.onclick = function(element) {
   //提取按钮颜色
  let color = element.target.value;
  chrome.tabs.query({active: true, currentWindow: true}, function(tabs) {
      //把tab页的背景色设置为按钮的颜色
    chrome.tabs.executeScript(
        tabs[0].id,
        {code: 'document.body.style.backgroundColor = "' + color + '";'});
  });
};