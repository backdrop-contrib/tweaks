<?php

/**
 * @file
 * Admin page callbacks for the tweaks_language_switcher module.
 */


/**
 * Form builder; The language switcher form.
 */
function tweaks_language_switcher_settings($form, $form_state) {

  $config = config('tweaks_language_switcher.settings');

  $form['path'] = array(
    '#type' => 'radios',
    '#title' => t('Translations path'),
    '#description' => t('The path of the language links of the Language Switcher block.'),
    '#default_value' => $config->get('path'),
    '#options' => array(
      'default' => t('Current page'),
      'front' => t('Front page'),
    ),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration')
  );

  return $form;
}

function tweaks_language_switcher_settings_submit($form, &$form_state) {

  $config = config('tweaks_language_switcher.settings');
  $config->set('path', $form_state['values']['path']);
  $config->save();

  backdrop_set_message(t('The configuration options have been saved.'));
}
