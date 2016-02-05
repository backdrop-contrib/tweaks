
(function ($) {

/**
 * Collapse groups on Permissions page.
 */
Backdrop.behaviors.collapseGroupsPermissionsPage = {
  attach: function (context, settings) {
    // Freeze width of first column to prevent jumping.
    $('#permissions th:first', context).css({ width: $('#permissions th:first', context).width() });
    // Attach click handler.
    $modules = $('#permissions tr:has(td.module)', context).once('collapse-permissions-page', function () {
      var $module = $(this);
      $module.bind('click.collapseGroups', function () {
        // @todo Replace with .nextUntil() in jQuery 1.4.
        $module.nextAll().each(function () {
          var $row = $(this);
          if ($row.is(':has(td.module)')) {
            return false;
          }
          $row.toggleClass('element-hidden');
        });
      });
    });
    // Collapse all but the targeted permission rows set.
    if (window.location.hash.length) {
      $modules = $modules.not(':has(' + window.location.hash + ')');
    }
    $modules.trigger('click.collapseGroups');
  }
};

})(jQuery);
