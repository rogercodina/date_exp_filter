<?php

/**
 * @file
 * Views custom exposed filter months plugin.
 * https://www.drupal.org/node/292667
 */

class date_exp_filter_handler_filter_changed extends views_handler_filter {

  function can_expose() { return TRUE; }

  /**
   * Implements views_object#admin_summary().
   */
  function admin_summary() {
    return t('Filters by changed date');
  }

  /**
   * Options form subform for setting exposed filter options.
   */
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);

    $timepicker = date_popup_get_preferred_timepicker();

    $form['value']['changed_from'] = array(
       '#type' => 'date_popup',
       '#date_type' => DATE_DATETIME,
       '#date_timezone' => date_default_timezone(),
       '#date_format' => 'd-m-Y',
       '#datepicker_options' => array(),
       '#timepicker' => variable_get('date_popup_timepicker', $timepicker),
       '#date_year_range' => '-3:+3',
       //'#title' => t('Updated date'),
       '#default_value' => 0,
       '#attributes' =>array('placeholder' => t('Updated date')),
   );

    $form['value']['changed_until'] = array(
       '#type' => 'date_popup',
       '#date_type' => DATE_DATETIME,
       '#date_timezone' => date_default_timezone(),
       '#date_format' => 'd-m-Y',
       '#datepicker_options' => array(),
       '#timepicker' => variable_get('date_popup_timepicker', $timepicker),
       '#date_year_range' => '-3:+3',
       //'#title' => t('Until'),
       '#default_value' => 0,
       '#attributes' =>array('placeholder' => t('Until')),
   );

  }

  /**
   * Alters Views query when filter is used.
   * Nomes s'executa si el filtre no es exposat.
   * Per aixo hem implementat el hook_views_query_alter a l'altre fitxer.
   */
  /*function query() {}*/
}
