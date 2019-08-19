<?php

/**
 * @file
 * Call back function for various services.
 */

/**
 * Callback function for creating greeting content type.
 *
 * @param object $data
 *   The data values.
 *
 * @return object
 *   The url and node details
 */
function _mycorp_greeting_content_create($data) {
  global $user;
  if (isset($data) && is_array($data)) {
    $data = (object) $data;
  }
  unset($data->nid);
  $data->uid = $user->uid;
  $data->created = time();
  $data->modified = time();
  $data->type = 'greeting';
  $data->is_new = TRUE;
  if (!isset($data->title)) {
    if (isset($data->field_greeting_title)) {
      if (is_array($data->field_greeting_title)) {
        $data->title = $data->field_greeting_title[LANGUAGE_NONE][0]['value'];
      }
      else {
        $data->title = $data->field_greeting_title;
      }
    }
    else {
      return services_error('Missing greeting attribute title', 406);
    }
  }
  if (isset($data->field_greeting_title) && !is_array($data->field_greeting_title)) {
    $field_greeting_title = $data->field_greeting_title;
    $data->field_greeting_title = array();
    $data->field_greeting_title[LANGUAGE_NONE][0]['value'] = $field_greeting_title;
  }
  if (isset($data->field_greeting_image) && !is_array($data->field_greeting_image)) {
    $image = file_get_contents($data->field_greeting_image);
    $basename = drupal_basename($data->field_greeting_image);
    $file_name = !empty($basename) ? file_build_uri($basename) : NULL;
    $file = file_save_data($image, $file_name, FILE_EXISTS_RENAME);
    if (is_object($file)) {
      if (isset($file->fid)) {
        $data->field_greeting_image = array();
        $data->field_greeting_image[LANGUAGE_NONE]['0']['fid'] = $file->fid;
      }
    }
  }

  node_save($data);

  return (object) array(
    'nid' => $data->nid,
    'uri' => services_resource_uri(array('greetings', $data->nid)),
  );
}

/**
 * Callback for fetching greeting content type.
 *
 * @param int $nid
 *   The node id of the greeting node.
 *
 * @return object
 *   The node details of  greeting content type.
 */
function _mycorp_greeting_content_retrieve($nid) {
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_greeting_image', 'gi', 'gi.entity_id = n.nid');
  $query->leftJoin('field_data_field_greeting_title', 'gt', 'gt.entity_id = n.nid');
  $results = $query->fields('n', array('nid', 'title'))
    ->fields('gi', array('field_greeting_image_fid'))
    ->fields('gt', array('field_greeting_title_value'))
    ->condition('n.nid', $nid)
    ->execute()
    ->fetchAll();

  foreach ($results as $key => $data) {
    if (!empty($data->field_greeting_image_fid)) {
      $file = file_load($data->field_greeting_image_fid);
      $results[$key]->field_greeting_image_url = file_create_url($file->uri);
    }
  }

  return $results;
}

/**
 * Callback for listing all greeting content.
 */
function _mycorp_greeting_content_index() {
  $query = db_select('node', 'n');
  $query->leftJoin('field_data_field_greeting_image', 'gi', 'gi.entity_id = n.nid');
  $query->leftJoin('field_data_field_greeting_title', 'gt', 'gt.entity_id = n.nid');
  $results = $query->fields('n', array('nid', 'title'))
    ->fields('gi', array('field_greeting_image_fid'))
    ->fields('gt', array('field_greeting_title_value'))
    ->execute()
    ->fetchAll();

  foreach ($results as $key => $data) {
    if (!empty($data->field_greeting_image_fid)) {
      $file = file_load($data->field_greeting_image_fid);
      $results[$key]->field_greeting_image_url = file_create_url($file->uri);
    }
  }

  return $results;
}

/**
 * Callback for updating the specific node of greeting content type.
 */
function _mycorp_greeting_content_node_update($nid, $data) {
  global $user;
  if (is_numeric($nid)) {
    if (isset($data) && is_array($data)) {
      $data = (object) $data;
      if ($data->nid == $nid) {
        $node = node_load($nid);
        unset($node->created);
        $node->id = $nid;
        $node->uid = $user->uid;
        $node->modified = time();
        $node->type = 'greeting';
        if (isset($data->title)) {
          if (!is_array($data->title)) {
            $node->title = $data->title;
          }
        }
        if (isset($data->field_greeting_title) && !is_array($data->field_greeting_title)) {
          $field_greeting_title = $data->field_greeting_title;
          $node->field_greeting_title = array();
          $node->field_greeting_title[LANGUAGE_NONE][0]['value'] = $field_greeting_title;
        }
        if (isset($data->field_greeting_image) && !is_array($data->field_greeting_image)) {
          $image = file_get_contents($data->field_greeting_image);
          $basename = drupal_basename($data->field_greeting_image);
          $file_name = !empty($basename) ? file_build_uri($basename) : NULL;
          $file = file_save_data($image, $file_name, FILE_EXISTS_RENAME);
          if (is_object($file)) {
            if (isset($file->fid)) {
              $node->field_greeting_image = array();
              $node->field_greeting_image[LANGUAGE_NONE]['0']['fid'] = $file->fid;
            }
          }
        }
        node_save($node);
        return (object) array(
          'id' => $nid,
          'uri' => services_resource_uri(array('greetings', $nid)),
        );
      }
      else {
        return services_error('Node Id does not match with the url parameter.', 406);
      }
    }

  }
  else {
    return services_error('Node Id does not match with the url parameter.', 406);
  }
}

/**
 * Callback for deleting the specific node of greeting content type.
 */
function _mycorp_greeting_content_node_delete($nid) {
  if (is_numeric($nid)) {
    $node = node_load($nid);
    if (is_object($node) && !empty($node)) {
      if ($node->type == 'greeting') {
        node_delete($nid);
        return t('Greeting Content type node is Deleted');
      }
      else {
        return services_error('Node id passed doesnot belong to a Greeting node.', 406);
      }
    }
    else {
      return services_error('Node id does not exists.', 406);
    }

  }
  else {
    return services_error('Invalid data passed for node id.', 406);
  }
}

/**
 * Callback for publishing & unpublishing the node of greeting content type.
 */
function _mycorp_greeting_content_node_pubish_unpublish($nid) {
  if (is_numeric($nid)) {
    $node = node_load($nid);
    if (is_object($node) && !empty($node)) {
      if ($node->type == 'greeting') {
        if ($node->status) {
          $node->status = 0;
          node_save($node);
          return t('Greeting node has been unpublished');
        }
        else {
          $node->status = 1;
          node_save($node);
          return t('Greeting node has been published');
        }
      }
      else {
        return services_error('Node id passed doesnot belong to a Greeting node.', 406);
      }
    }
    else {
      return services_error('Invalid data passed for node id.', 406);
    }
  }
  else {
    return services_error('Invalid data passed for node id.', 406);
  }
}
