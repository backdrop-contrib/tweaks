<?php

/**
 * @file
 * Theme functions for the tweaks_modules_weight module.
 */


/**
 * Returns HTML for the modules form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_tweaks_modules_weight_system_modules_fieldset($variables) {
  $form = $variables['form'];

  // Individual table headers.
  $rows = array();
  // Iterate through all the modules, which are
  // children of this fieldset.
  foreach (element_children($form) as $key) {
    // Stick the key into $module for easier access.
    $module = $form[$key];
    // Create the row for the table.
    $row = array();
    unset($module['enable']['#title']);
    $module['#requires'] = array_filter($module['#requires']);
    $module['#required_by'] = array_filter($module['#required_by']);

    $requires = !empty($module['#requires']);
    $required_by = !empty($module['#required_by']);
    $requirements = '';
    $toggle = '';

    // Add the first column: the checkbox.
    $row[] = array('class' => array('checkbox'), 'data' => backdrop_render($module['enable']));

    // Add the second column: module label and expand/collapse functionalty.
    $row[] = array('class' => array('module'), 'data' => '<label id="module-' . $key . '" for="' . $module['enable']['#id'] . '" class="module-name table-filter-text-source">' . backdrop_render($module['name']) . '</label>');

    // Add the third column: module version number.
    $row[] = array('class' => array('version'), 'data' => backdrop_render($module['version']));

    // Add the weight column: module weight.
    $row[] = array('class' => array('weight'), 'data' => backdrop_render($module['weight']));

    if ($requires || $required_by) {
      $requirements .= ' <div class="requirements">';
      if ($requires) {
        $requirements .= '<div class="admin-requirements">' . t('Requires: !module-list', array('!module-list' => implode(', ', $module['#requires']))) . '</div>';
      }
      if ($required_by) {
        $requirements .= '<div class="admin-requirements">' . t('Required by: !module-list', array('!module-list' => implode(', ', $module['#required_by']))) . '</div>';
      }
      $requirements .= '</div>';

      // Build a requirements toggle.
      $toggle .= ' <a class="requirements-toggle" href="#">' . t('more') . '</a>';
    }

    // Add the description, along with any modules it requires.
    $details = '<div class="text table-filter-text-source"> ' . backdrop_render($module['description']) . $toggle . '</div>' . $requirements;

    // Add the fourth column: description, along with any modules it requires.
    $row[] = array('class' => array('description'), 'data' => $details);

    // Add the fifth column: links (such as configure or permissions) in their own columns.
    $row[] = array('data' => backdrop_render($module['links']), 'class' => array('operations'));

    // Hide modules that can't be disabled at all.
    if (!$module["#required_by_distribution"]) {
      $rows[] = $row;
    }
  }

  return theme('table', array('header' => $form['#header'], 'rows' => $rows));
}
