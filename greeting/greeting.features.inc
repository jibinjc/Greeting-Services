<?php

/**
 * @file
 * greeting.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function greeting_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_node_info().
 */
function greeting_node_info() {
  $items = array(
    'greeting' => array(
      'name' => t('Greeting'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
