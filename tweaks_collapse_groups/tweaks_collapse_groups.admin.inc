<?php

/**
 * @file
 * Admin page callbacks for the tweaks_collapse_groups module.
 */


/**
 * Form builder; The module groups form.
 */
function tweaks_collapse_groups_settings($form, $form_state) {

  $config = config('tweaks_collapse_groups.settings');

  $form['collapse_modules_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapse groups on the <a href="!modules">Modules</a> page', array(
      '!modules' => url('admin/modules'),
    )),
    '#default_value' => $config->get('collapse_modules_page'),
  );
  $form['collapse_permissions_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapse groups on the <a href="!permissions">Permissions</a> page', array(
      '!permissions' => url('admin/config/people/permissions'),
    )),
    '#default_value' => $config->get('collapse_permissions_page'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration')
  );

  return $form;
}

function tweaks_collapse_groups_settings_submit($form, &$form_state) {

  $config = config('tweaks_collapse_groups.settings');
  $config->set('collapse_modules_page', $form_state['values']['collapse_modules_page']);
  $config->set('collapse_permissions_page', $form_state['values']['collapse_permissions_page']);
  $config->save();

  backdrop_set_message(t('The configuration options have been saved.'));
}
