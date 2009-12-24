<?php
// $Id$

/**
 * @file
 * Page callbacks and utility functions for IP anonymize module.
 */

/**
 * Anonymize IP addresses which have exceeded the retention period. 
 */
function ip_anon_scrub() {
  foreach (ip_anon_tables() as $table => $columns) {
    db_update($table)
      ->fields(array($columns['hostname'] => 0))
      ->condition($columns['timestamp'], REQUEST_TIME - variable_get('ip_anon_period_'. $table, 21600), '<')
      ->execute();
  }
}

/**
 * Configuration options for IP anonymize.
 */
function ip_anon_settings() {
  $form = array();
  $form['ip_anon_policy'] = array(
    '#type' => 'radios',
    '#title' => t('Retention policy'),
    '#options' => array(0 => t('Preserve IP addresses'), 1 => t('Anonymize IP addresses')),
    '#description' => t('This setting may be used to temporarily disable IP anonymization.'),
    '#default_value' => 0,
  );
  $form['ip_anon_period'] = array(
    '#type' => 'fieldset',
    '#title' => t('Retention period'),
    '#description' => t('IP addresses older than the retention period will be anonymized.'),
  );
  $options = drupal_map_assoc(array(0, 30, 60, 120, 180, 300, 600, 900, 1800, 2700, 3600, 5400, 7200, 10800, 21600, 32400, 43200, 64800, 86400, 172800, 259200, 345600, 604800, 1209600, 2419200, 4838400, 9676800, 31536000), 'format_interval');
  foreach (ip_anon_tables() as $table => $columns) {
    $schema = drupal_get_schema($table);
    $form['ip_anon_period']['ip_anon_period_' . $table] = array(
      '#type' => 'select',
      '#title' => t('@table table', array('@table' => $table)),
      '#options' => $options,
      '#default_value' => 21600,
      '#description' => t($schema['description']),
    );
  }
  return system_settings_form($form);
}

/**
 * Array of tables and columns which store hostnames and timestamps.
 * Other modules may use hook_ip_anon_alter() to add tables:
 * function my_module_ip_anon_alter(&$tables) {
 *   $tables['my_table_name'] = array(
 *     'hostname' => 'my_hostname_column',
 *     'timestamp' => 'my_timestamp_column',
 *   );
 * }
 */
function ip_anon_tables() {
  $columns = drupal_map_assoc(array('hostname', 'timestamp'));
  $tables = array_fill_keys(array('accesslog', 'comment', 'sessions', 'watchdog'), $columns);
  drupal_alter('ip_anon', $tables);
  foreach ($tables as $table => $columns) {
    if (!db_table_exists($table)) {
      unset($tables[$table]);
    }
  }
  return $tables;
}
