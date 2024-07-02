var minWidth = 0;
var minHeight = 0;

var maxWidth = 1500;
var maxHeight = 1500;

$(document).ready(function() {
    $('#dialog').hide(); 

    $('#openDialog').click(function() {
      $('#dialog').show();
    });
  
    $('.close-btn').click(function() {
      $('#dialog').hide();
    });

    $('#set-button').click(function() {
        minWidth = parseInt($('#min-width').val());
        minHeight = parseInt($('#min-height').val());
        maxWidth = parseInt($('#max-width').val());
        maxHeight = parseInt($('#max-height').val());
    });
  
    var isResizing = false;
    $(document).on('mousedown', '.resizer', function(event) {
      event.preventDefault();
      isResizing = true;
      var startX = event.pageX;
      var startY = event.pageY;
      var startWidth = $('#dialog').width();
      var startHeight = $('#dialog').height();
  
      $(document).on('mousemove', function(event) {
        if (isResizing) {   
            console.log(minWidth);
            console.log(minHeight);
          var newWidth = startWidth + (event.pageX - startX);
          var newHeight = startHeight + (event.pageY - startY);

        if (newWidth < minWidth) {
        newWidth = minWidth;
        }

        if (newHeight < minHeight) {
            newHeight = minHeight;
        }

        if (newWidth > maxWidth) {
            newWidth = maxWidth;
        }

        if (newHeight > maxHeight) {
            newHeight = maxHeight;
        }
        
          $('#dialog').css({
            'width': newWidth,
            'height': newHeight
          });
        }
      }).on('mouseup', function() {
        isResizing = false;
        $(document).off('mousemove');
      });
    });
  
    $(document).on('mouseup', function() {
      isResizing = false;
      $(document).off('mousemove');
    });
  });
  