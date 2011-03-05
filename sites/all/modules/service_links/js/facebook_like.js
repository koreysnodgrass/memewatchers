(function ($) {
  $(document).ready(function(){
    $('a.service-links-facebook-like').each(function(){
      iframe_txt='<iframe src="' + $(this).attr('href') + '&amp;layout=' + $(this).attr('layout') + '&amp;show_faces=false&amp;width=' + $(this).attr('width') + '&amp;action='+ $(this).attr('action') + '&amp;colorscheme=' + $(this).attr('colorscheme') + '&amp;height=' + $(this).attr('height') + '" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width:' + $(this).attr('width') + 'px; height:' + $(this).attr('height') + 'px;"' + ' allowTransparency="true"></iframe>';
      $(this).replaceWith(iframe_txt);
    });
  });
})(jQuery);
