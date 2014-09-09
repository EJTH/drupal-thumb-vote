<?php
/**
 * drupal_get_form callback
 * @return array
 */
function thumb_vote_admin_settings(){
  
  /*
   * Get entity type options, and list them neatly in the
   * admin form with main entity type as headline.
   */
  
  $form['thumbvote_entity_type_fieldset'] = array(
    '#type'     => 'fieldset',
    '#title'    => t('Enable vote for content types'),
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,

  );
  
  $entity_info = entity_get_info();
  
  foreach($entity_info as $k => $i){
    $options = array();
    
    if(isset($i['bundles'])){
      foreach($i['bundles'] as $bk => $b){
        $options[$bk] = $b['label'];
      }
    }
    
    $form['thumbvote_entity_type_fieldset']['thumbvote_entity_types_'.$k] = array(
      '#type'     => 'checkboxes',
      '#title'    => $i['label'],
      '#options'  => $options,
      '#default_value'  => variable_get('thumbvote_entity_types_'.$k, array()),
    );
    
  }
  
  /*
   * Display options
   */

  $form['thumbvote_display_settings'] = array(
    '#title' => t('Display options'),
    '#type'  => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE
  );
  
  
  $form['thumbvote_display_settings']['thumbvote_render_weight'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Layout/render weight'),
    '#default_value' => variable_get('thumbvote_render_weight',-1),
    '#description'   => t('Layout / render weight of the rating GUI, lower means 
        it would be displated higher up in the DOM, higher 
        value would make it go further down the DOM')
  );

  $display_options = array(
    0 => t('Don\'t show ratings'),
    1 => t('Show sum of votes'),
    2 => t('Show positive and negative vote count'),
    3 => t('Show positive votes as percentage')
  );
  
  $form['thumbvote_display_settings']['thumbvote_display_mode'] = array(
    '#type'     => 'radios',
    '#title'    => t('Display mode'),
    '#default_value' => variable_get('thumbvote_display_mode',1),
    '#description'   => t('How the vote result is displayed'),
    '#options'       => $display_options
  );
  

  $form['#submit'][] = 'thumb_vote_form_submit';

  return system_settings_form($form);
}

/**
 * Form submit hook. Unused declared because why not?
 * @param type $form
 * @param type $form_state
 */
function thumb_vote_form_submit($form, $form_state){
  $entity_info = entity_get_info();
  
  
  $entity_types = array();
  
  foreach($entity_info as $k => $i){
    foreach($form_state['values']['thumbvote_entity_types_'.$k] as $enttype){
      if($enttype){
        $entity_types[] = $enttype;
      }
    }
  }
  variable_set('thumbvote_entity_types',$entity_types);
}