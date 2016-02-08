<?php

/**
 * @file
 * Admin page callbacks for the tweaks_modules_weight module.
 */


/**
 * Form builder; The modules weight settings form.
 */
function tweaks_modules_weight_settings($form, $form_state) {

  $config = config('tweaks_modules_weight.settings');

  $form['modules_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Modules weight'),
    '#description' => t('Display the modules weight on the <a href="!modules">Modules</a> page.', array(
      '!modules' => url('admin/modules'),
    )),
    '#default_value' => $config->get('modules_weight'),
    '#options' => array(
      'display' => t('Display'),
      'none' => t('None'),
    ),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration')
  );

  return $form;
}

function tweaks_modules_weight_settings_submit($form, &$form_state) {

  $config = config('tweaks_modules_weight.settings');
  $config->set('modules_weight', $form_state['values']['modules_weight']);
  $config->save();

  backdrop_set_message(t('The configuration options have been saved.'));
}
