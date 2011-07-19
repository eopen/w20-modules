<?php

function w20_folder_page_add () {

	$output .= theme('image', 'sites/all/modules/w20_folder/img/folder.gif') . ' ' . w20_folder_breadcrumb((int) arg(4)) . '<br /> <br />';
	$output .= drupal_get_form('w20_folder_page_add_form', (int) arg(2)) . '<br />';
	
	return $output;

}


function w20_folder_page_add_form(&$form_state, $parent) {
    // o $tid desta função, é o id do termo pai
  
	$form['new_title'] = array(
		'#type' => 'textfield',
		'#title' => "Title",
		'#size' => 40,
		'#required' => TRUE,
		
	);
	$form['new_body'] = array(
		'#type' => 'textarea',
		'#title' => "Body",
		'#required' => TRUE,
	);

	$form['tid'] = array(
		'#type' => 'hidden',
		'#title' => '', 
		'#value' => arg(4),
	);
	
    //Submit button:
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Salvar'),
		'#submit' => array('w20_folder_page_add_form_submit'),

	);
	$form['cancel'] = array(
		'#type' => 'button',
		'#attributes' => array('onClick' => 'location.replace("'. referer_uri() .'"); return false;'),
		'#value' => t('Cancelar'),
	);


   
    return $form;
}

function w20_folder_page_add_form_validate($form, &$form_state) {
    $w20_folder_taxonomia = $form_state['values']['name'];
    if (isset($w20_folder_taxonomia)) {
        if (!is_string($w20_folder_taxonomia) || $w20_folder_taxonomia == '') {
            form_set_error('w20_folder_taxonomia', t('Digite um nome pra pasta'));
        }
    }
}

function w20_folder_page_add_form_submit($form, &$form_state) {
    global $vfid, $user;
		
	$node = new StdClass();
	$node->type = 'page';
	$node->status = 1;
	$node->uid = $user->uid;
	$node->title = $form_state['values']['new_title'];
	$node->body = $form_state['values']['new_body'];
	$node->language = 'pt-br';
	node_save($node);

	$last_id = db_result(db_query('SELECT nid FROM {node} ORDER BY nid DESC LIMIT 1 ')); //db_last_insert_id('node', 'nid');
	$nload = node_load($last_id);
	$exe_query = taxonomy_node_save($nload, array('0' => $form_state['values']['tid']));
	 
	if ($exe_query !== false) {
        watchdog('w20_patas', 'Added message to log: %id', array('%id'=>$last_id), WATCHDOG_INFO);
        drupal_set_message(t('Página criada com sucesso. '));
    } else {
        watchdog('w20_patas', 'Could not add message to log: ', array(), WATCHDOG_ERROR);
        drupal_set_message(t('A página não foi salva com sucesso.'));
    }

	$form_state['redirect'] = 'w20/folder/' . $form_state['values']['tid'];
	
}


?>
