<?php
/**
*
* Block comment
*
**/

/**
 * Implements hook_update_projects_alter().
 */
function distroteq_blacklist_update_projects_alter(&$projects) {
  //add modules to this array
  $blacklist = array(
    'admin_menu',
    'admin_views',
    'bean',
    'better_exposed_filters',
    'block_class',
    'blockify',
    'breakpoints',
    'ckeditor',
    'ctools',
    'devel',
    'entity',
    'entityreference',
    'features',
    'libraries',
    'link',
    'menu_attributes',
    'menu_block',
    'metatag',
    'module_filter',
    'pathauto',
    'picture',
    'token',
    'transliteration',
    'vide_embed_field',
    'views',
    'views_bulk_operations',
    'webform',
    'xmlsitemap',
  );
  foreach ($blacklist as $module) {
    unset($projects[$module]);
  }

}

//that's all she wrote