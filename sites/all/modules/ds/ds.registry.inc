<?php

/**
 * @file
 * Registry file for Display Suite.
 */

/**
 * Implements hook_menu().
 */
function _ds_menu() {
  $items = array();

  // Start page of Display Suite.
  $items['admin/structure/ds'] = array(
    'title' => 'Display suite',
    'description' => 'Manage configuration for Display Suite.',
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('access administration pages'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
  );

  // Custom styles.
  $items['admin/structure/ds/styles'] = array(
    'title' => 'Styles',
    'description' => 'Define classes which you can use as classes for regions.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_styles_form'),
    'file' => 'ds.styles.inc',
    'access arguments' => array('admin_display_suite'),
  );

  // Layout overview.
  $items['admin/structure/ds/layout'] = array(
    'title' => 'Layout',
    'description' => 'Displays an overview of all entities.',
    'page callback' => 'ds_layout_list',
    'file' => 'ds.layout.inc',
    'access arguments' => array('admin_display_suite'),
  );

  // Revert layout.
  $items['admin/structure/ds/revert-layout'] = array(
    'title' => 'Revert layout',
    'description' => 'Revert layout and field settings.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_revert_layout_field_settings_form'),
    'file' => 'ds.field_ui.inc',
    'access arguments' => array('admin_display_suite'),
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );

  // View modes.
  $items['admin/structure/ds/view_modes'] = array(
    'title' => 'View modes',
    'description' => 'Manage view modes for all content.',
    'page callback' => 'ds_view_modes_list',
    'file' => 'ds.view_modes.inc',
    'access arguments' => array('admin_view_modes'),
  );
  $items['admin/structure/ds/view_modes/manage'] = array(
    'title' => 'Add a view mode',
    'description' => 'Manage a view mode',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_edit_view_mode_form'),
    'file' => 'ds.view_modes.inc',
    'access arguments' => array('admin_view_modes'),
    'type' => MENU_LOCAL_ACTION,
  );
  $items['admin/structure/ds/view_modes/delete'] = array(
    'title' => 'Delete a view mode',
    'description' => 'Delete a custom view mode.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_delete_view_mode_confirm'),
    'file' => 'ds.view_modes.inc',
    'access arguments' => array('admin_view_modes'),
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );
  $items['admin/structure/ds/view_modes/revert'] = array(
    'title' => 'Revert a view mode',
    'description' => 'Revert a view mode.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_revert_view_mode_confirm'),
    'file' => 'ds.view_modes.inc',
    'access arguments' => array('admin_view_modes'),
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );

  // Fields.
  $items['admin/structure/ds/fields'] = array(
    'title' => 'Fields',
    'description' => 'Manage fields for all content.',
    'page callback' => 'ds_custom_fields_list',
    'file' => 'ds.fields.inc',
    'access arguments' => array('admin_fields'),
  );
  $items['admin/structure/ds/fields/manage'] = array(
    'title' => 'Fields edit',
    'page callback' => 'ds_custom_manage',
    'file' => 'ds.fields.inc',
    'access arguments' => array('admin_fields'),
    'type' => MENU_CALLBACK,
  );
  $items['admin/structure/ds/fields/manage_custom'] = array(
    'title' => 'Add a field',
    'description' => 'Manage a field',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_edit_custom_field_form'),
    'file' => 'ds.fields.inc',
    'access arguments' => array('admin_view_modes'),
    'type' => MENU_LOCAL_ACTION,
    'weight' => 0,
  );
  $items['admin/structure/ds/fields/delete'] = array(
    'title' => 'Delete a field',
    'description' => 'Delete a field.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_delete_field_confirm'),
    'file' => 'ds.fields.inc',
    'access arguments' => array('admin_fields'),
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );
  $items['admin/structure/ds/fields/revert'] = array(
    'title' => 'Revert a custom field',
    'description' => 'Revert a custom field.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ds_revert_field_confirm'),
    'file' => 'ds.fields.inc',
    'access arguments' => array('admin_fields'),
    'type' => MENU_VISIBLE_IN_BREADCRUMB,
  );
  // Block can be disabled.
  if (module_exists('block')) {
    $items['admin/structure/ds/fields/manage_block'] = array(
      'title' => 'Add a block field',
      'description' => 'Manage a block field',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('ds_edit_block_field_form'),
      'file' => 'ds.fields.inc',
      'access arguments' => array('admin_view_modes'),
      'type' => MENU_LOCAL_ACTION,
      'weight' => 1,
    );
  }

  return $items;
}

/**
 * Implements hook_theme().
 */
function _ds_theme() {
  $theme_functions = array();

  // Layouts
  $layouts = module_invoke_all('ds_layout_info');
  foreach ($layouts as $key => $layout) {
    $theme_functions[$key] = array(
      'render element' => 'elements',
      'template' => strtr($key, '_', '-'),
      'path' => $layout['path'],
    );
  }

  return $theme_functions;
}

/**
 * Implements hook_theme_registry_alter().
 */
function _ds_theme_registry_alter(&$theme_registry) {

  // Inject ds_entity_variables in all entity theming functions.
  $entity_info = entity_get_info();
  foreach ($entity_info as $entity => $info) {
    if (isset($entity_info[$entity]['fieldable']) && $entity_info[$entity]['fieldable']) {
      // User uses user_profile for theming.
      if ($entity == 'user') $entity = 'user_profile';
      $theme_registry[$entity]['preprocess functions'][] = 'ds_entity_variables';
    }
  }
}

/**
 * Implements hook_entity_info_alter().
 */
function _ds_entity_info_alter(&$entity_info) {

  ctools_include('export');

  // Add custom view modes to entities.
  $custom_view_modes = ctools_export_load_object('ds_view_modes');
  foreach ($custom_view_modes as $view_mode_key => $view_mode_value) {
    $view_mode = array(
      'label' => check_plain($view_mode_value->label),
      'custom settings' => FALSE,
    );
    foreach ($view_mode_value->entities as $entity_type) {
      if (isset($entity_info[$entity_type])) {
        $entity_info[$entity_type]['view modes'][$view_mode_key] = $view_mode;
      }
    }
  }

  // Add layout if applicable.
  $ds_layouts = module_invoke_all('ds_layout_info');
  $ds_layout_settings = ctools_export_load_object('ds_layout_settings');
  foreach ($ds_layout_settings as $row) {
    $layout = $ds_layouts[$row->layout];
    $layout['layout'] = $row->layout;
    $layout['settings'] = $row->settings;
    $entity_info[$row->entity_type]['bundles'][$row->bundle]['layouts'][$row->view_mode] = $layout;
  }
}

/**
 * Implements hook_ds_layout_info().
 */
function _ds_ds_layout_info() {
  $path = drupal_get_path('module', 'ds');
  $layouts = array(
    'ds_1col' => array(
      'label' => t('One column'),
      'path' => $path . '/layouts/ds_1col',
      'regions' => array(
        'ds_content' => t('Content'),
      ),
    ),
    'ds_2col' => array(
      'label' => t('Two column'),
      'path' => $path . '/layouts/ds_2col',
      'regions' => array(
        'left' => t('Left'),
        'right' => t('Right')
      ),
      'css' => TRUE,
    ),
    'ds_2col_stacked' => array(
      'label' => t('Two column stacked'),
      'path' => $path . '/layouts/ds_2col_stacked',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_2col_stacked_fluid' => array(
      'label' => t('Two column stacked - fluid'),
      'path' => $path . '/layouts/ds_2col_stacked_fluid',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_3col' => array(
      'label' => t('Three column - 25/50/25'),
      'path' => $path . '/layouts/ds_3col',
      'regions' => array(
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_equal_width' => array(
      'label' => t('Three column - equal width'),
      'path' => $path . '/layouts/ds_3col_equal_width',
      'regions' => array(
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_stacked' => array(
      'label' => t('Three column stacked - 25/50/25'),
      'path' => $path . '/layouts/ds_3col_stacked',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_stacked_equal_width' => array(
      'label' => t('Three column stacked - equal width'),
      'path' => $path . '/layouts/ds_3col_stacked_equal_width',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_3col_stacked_html5' => array(
      'label' => t('Three column stacked - 25/50/25 (HTML5)'),
      'path' => $path . '/layouts/ds_3col_stacked_html5',
      'regions' => array(
        'header' => t('Header'),
        'left' => t('Left'),
        'middle' => t('Middle'),
        'right' => t('Right'),
        'footer' => t('Footer'),
      ),
      'css' => TRUE,
    ),
    'ds_4col' => array(
      'label' => t('Four column - equal width'),
      'path' => $path . '/layouts/ds_4col',
      'regions' => array(
        'first' => t('First'),
        'second' => t('Second'),
        'third' => t('Third'),
        'fourth' => t('Fourth'),
      ),
       'css' => TRUE,
    ),
  );

  // Get layouts defined in the default theme and base theme (if applicable).
  $theme = variable_get('theme_default');
  $themes = list_themes();

  $base_theme = array();
  $ancestor = $theme;
  while ($ancestor && isset($themes[$ancestor]->base_theme)) {
    $ancestor = $themes[$ancestor]->base_theme;
    $base_theme[] = $themes[$ancestor];
  }


  foreach (array_reverse($base_theme) as $base) {
    _ds_layouts_scan_theme($base->name, $layouts);
  }
  _ds_layouts_scan_theme($theme, $layouts);

  return $layouts;
}

function _ds_layouts_scan_theme($theme, &$layouts) {
  $theme_layouts = file_scan_directory(drupal_get_path('theme', $theme) . '/ds_layouts', '/inc/');
  foreach ($theme_layouts as $file => $values) {
    include_once(DRUPAL_ROOT . '/' . $file);
    $function = 'ds_' . $values->name;
    $layouts[$values->name] = $function();
    $layouts[$values->name]['path'] = str_replace('/' . $values->filename, '', $file);
  }
}