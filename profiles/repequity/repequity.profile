<?php

function pantheon_install_tasks($install_state) {
  $tasks = array (
    'repequity_configure' => array(),
  );
  return $tasks;
}

/**
 * Set up base config
 */
function repequity_configure() {
  // Set default RE variables
  variable_set('cache', 1);
  variable_set('block_cache', 1);
  variable_set('cache_lifetime', '0');
  variable_set('page_cache_maximum_age', '900');
  variable_set('page_compression', 0);
  variable_set('preprocess_css', 1);
  variable_set('preprocess_js', 1);
  drupal_set_message(t('RepEquity defaults configured.'));
}
