<?php

function repequity_install_tasks($install_state) {
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
  $admin_menu = array(
    'admin_menu.icon' => TRUE,
    'admin_menu.menu' => TRUE,
    'admin_menu.search' => TRUE,
    'admin_menu.users' => TRUE,
    'admin_menu.account' => TRUE,
    'shortcut.links' => TRUE,
  );
  variable_set('admin_menu_components', $admin_menu);
  variable_set('user_register', USER_REGISTER_ADMINISTRATORS_ONLY);
  variable_set('admin_menu_margin_top', 1);
  variable_set('admin_menu_position_fixed', 1);
  variable_set('admin_menu_cache_client', 1);

  drupal_set_message(t('RepEquity defaults configured.'));
}
