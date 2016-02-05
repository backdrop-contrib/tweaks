<?php

/**
 * @file
 * Admin page callbacks for the tweaks_log_messages module.
 */


/**
 * Form builder; The log messages form.
 */
function tweaks_log_messages_settings($form, $form_state) {

  $config = config('tweaks_log_messages.settings');

  $form['clear_log_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the %clear button on the <a href="!dblog">Recent log messages</a> page', array(
      '%clear' => t('Clear log messages'),
      '!dblog' => url('admin/reports/dblog'),
    )),
    '#default_value' => $config->get('clear_log_form'),
  );
  $form['dblog_row_interval'] = array(
    '#type' => 'select',
    '#title' => t('Remove log messages older than'),
    '#description' => t('In order to work properly, it depends on the <a href="!cron">Cron</a> and <a href="!logging">Logging and errors</a> configurations. Requires a <a href="!status">cron maintenance task</a>.', array(
      '!cron' => url('admin/config/system/cron'),
      '!logging' => url('admin/config/development/logging'),
      '!status' => url('admin/reports/status'),
    )),
    '#default_value' => $config->get('dblog_row_interval'),
    '#options' => array(0 => t('Never')) + backdrop_map_assoc(array(86400, 172800, 604800, 1209600, 2592000, 5184000, 15552000, 31536000), 'format_interval'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration')
  );

  return $form;
}

function tweaks_log_messages_settings_submit($form, &$form_state) {

  $config = config('tweaks_log_messages.settings');
  $config->set('clear_log_form', $form_state['values']['clear_log_form']);
  $config->set('dblog_row_interval', $form_state['values']['dblog_row_interval']);
  $config->save();

  backdrop_set_message(t('The configuration options have been saved.'));
}
