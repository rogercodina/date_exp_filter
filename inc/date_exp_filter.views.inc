<?php

/**
 * @file
 * Views integration.
 */

/**
 * Implements hook_views_query_alter().
 *
 * Unica manera de modificar la query si el filtre estar exposat.
 */
function date_exp_filter_views_query_alter(&$view, &$query) {
  if (!empty($view->exposed_raw_input['changed_from']) || !empty($view->exposed_raw_input['changed_until'])) {
    $from = !empty($view->exposed_raw_input['changed_from']) ? strtotime($view->exposed_raw_input['changed_from']) : 0;
    $to = !empty($view->exposed_raw_input['changed_until']) ? strtotime($view->exposed_raw_input['changed_until']) : 0;

    if ($from != 0) {
      $query->add_where_expression(1, "node.changed >= :timestamp ", array(':timestamp' => $from));
    }
    if ($to != 0) {
      $query->add_where_expression(1, "node.changed <= :timestamp ", array(':timestamp' => $to));
    }

    //dpm($query);
  }
}


/**
 * Implements hook_search_api_views_query_alter().
 *
 * Unica manera de modificar la query si el filtre estar exposat.
 */
function date_exp_filter_search_api_views_query_alter(&$view, &$query) {
  /*
   * IMPORTANTE: Esta funcion SOLO se ejecuta para las vistas de Search API.
   */
 
  if (!empty($view->exposed_raw_input['changed_from']) || !empty($view->exposed_raw_input['changed_until'])) {
    $from = !empty($view->exposed_raw_input['changed_from']) ? strtotime($view->exposed_raw_input['changed_from']) : 0;
    $to = !empty($view->exposed_raw_input['changed_until']) ? strtotime($view->exposed_raw_input['changed_until']) : 0;

    /**
	   * IMPORTANT: Use field names that appear in admin/config/search/search_api/index/[INDEX_NAME]/fields
	   *
	   * NOTE: Search API stores dates as timestamps
	   *
	   * http://enzolutions.com/articles/2015/06/10/how-to-customize-a-search-api-filters-in-drupal-7/
	   * https://github.com/markaspot/mark-a-spot/blob/master/profiles/markaspot/modules/mark_a_spot/modules/markaspot_radar/markaspot_radar.module
	   */
   
    $main_filter = $query->createFilter('AND');
    if ($from != 0) {
      $main_filter->condition('changed', $from , '>=');
    }
    if ($to != 0) {
      $main_filter->condition('changed', $to , '<=');
    }

    $query->filter($main_filter);

    //dpm($query);
  }
}
