<?php
/**
 * drupal_get_form callback
 * @return array
 */
function thumb_vote_admin_settings(){
  //Get node type options.
  $types = node_type_get_types();
  $options = array();
  foreach($types as $n){
      $options[$n->type] = $n->name;
  }

  $form['thumbvote_node_types'] = array(
    '#type'     => 'checkboxes',
    '#title'    => t('Enable ratings for'),
    '#options'  => $options,
    '#default_value'  => variable_get('thumbvote_node_types', array('page')),
    '#description'    => t('Sets the content types rateable with this plugin')
  );
  
  $form['thumbvote_render_weight'] = array(
    '#type'     => 'textfield',
    '#title'    => t('Layout/render weight'),
    '#default_value' => variable_get('thumbvote_render_weight',-1),
    '#description'   => t('Layout / render weight of the rating GUI, lower means '
        . 'it would be displated higher up in the DOM, higher '
        . 'value would make it go further down the DOM')
  );

  $form['thumbvote_show_sum'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Display vote sum'),
    '#default_value' => variable_get('thumbvote_show_sum',true),
    '#description'   => t('Show vote result as summary')
  );


  $form['thumbvote_show_percentage'] = array(
    '#type'   => 'checkbox',
    '#title'  => t('Display vote percentage'),
    '#default_value'  => variable_get('thumbvote_show_percentage',true),
    '#description'    => t('Show total vote as positive percentage')
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
    
}