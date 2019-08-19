// $Id$

(function ($) {
  var mycorp_greeting = {
    'apiPath': '/api/v1/greetings'
  };

  // REST functions.
 /* mycorp_greeting.create = function (note, callback) {
    $.ajax({
      type: "POST",
      url: this.apiPath,
      data: JSON.stringify(note),
      dataType: 'json',
      contentType: 'application/json',
      success: callback
    });
  };

  mycorp_greeting.retreive = function (id, callback) {
    $.ajax({
      type: "GET",
      url: this.apiPath + '/' + id,
      dataType: 'json',
      success: callback
    });
  };

  mycorp_greeting.update = function (note, callback) {
    $.ajax({
      type: "PUT",
      url: this.apiPath + '/' + note.id,
      data: JSON.stringify(note),
      dataType: 'json',
      contentType: 'application/json',
      success: callback
    });
  };

  mycorp_greeting.del = function (id, callback) {
    $.ajax({
      type: "DELETE",
      url: this.apiPath + '/' + id,
      dataType: 'json',
      success: callback
    });
  };*/

  mycorp_greeting.index = function (callback) {
    $.getJSON(this.apiPath, callback);
  };




}(jQuery));