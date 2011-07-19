<?php

function w20_folder_edit() {
  global $user, $vfid;
  
	// form to edit the name
	$output = '<div class="w20-folder-container"><div class="w20-folder-breadcrumb"><div class="w20-folder-breadcrumb-img-folder">'.theme('image', 'sites/all/modules/w20_folder/img/folder.gif') . '</div> ' . w20_folder_breadcrumb(arg(2)) . '</div>';
	
	$output .= '<div class="w20-folder-container-build1"><div class="w20-folder-container-titulo-folder-edit">' . t('Editar pasta') . '</div>';
	$output .= drupal_get_form('w20_folder_edit_form', arg(2)).'</div>';
	
	// form to move all content do anouther folder
  	$output .= '<div class="w20-folder-container-build2"><div class="w20-folder-container-titulo-folder-edit2">' . t('Mover conteúdo para outra pasta') . '</div>';
	$output .= drupal_get_form('w20_folder_move_form', arg(2)).'</div>';
	
	// form to delete de folder
	//$children = taxonomy_get_tree(4, arg(2));
	//$taxo = taxonomy_select_nodes(array('0' => arg(2)), '', 0, FALSE);
	//if (count($children) > 0 OR db_affected_rows($taxo) > 0) $output .= t('Pastas com conteúdo não podem ser excluídas');
  	$output .= '<div class="w20-folder-container-build3"><div class="w20-folder-container-titulo-folder-edit3">' . t('Excluir definitivamente a pasta e todo o seu conteúdo') . '</div>';
	$output .= drupal_get_form('w20_folder_delete_form', arg(2)).'</div></div>';
	
	return $output;

}	

function w20_folder_edit_form(&$form_state, $tid) {
	global $vfid;
    // o $tid desta função é o id do termo e não de seu pai
  
	$saida = db_fetch_array(db_query("SELECT t.name, t.tid, p.parent FROM {term_data} AS t LEFT JOIN {term_hierarchy} AS p ON t.tid = p.tid WHERE t.tid = '" . $tid . "' LIMIT 1 "));
  	
	$form['name'] = array(
		'#type' => 'textfield',
		'#value' => $saida['name'],
		'#title' => t('Novo nome da pasta'),
		'#size' => 30,
		'#maxlength' => 30,
		'#prefix' => '<div class="w20-folder-edit-folder-new">',
		'#suffix' => '</div>',
	);

    $children = taxonomy_get_tree(4, $tid);

    // A term can't be the child of itself, nor of its children.
    $exclude =array();
	foreach ($children as $child) {
      $exclude[] = $child->tid;
    }
    $exclude[] = $tid;

   	$form['parent'] = _taxonomy_term_select('Pasta principal', 'parent', $saida['parent'], 4, '', null, '<' . t('Início') . '>', $exclude);

	$form['tid'] = array(
		'#type' => 'hidden',
		'#value' => $tid,
	);
	
    //Submit button:
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Salvar'),
		'#submit' => array('w20_folder_edit_form_submit'),
		'#prefix' => '<div class="w20-folder-edit-folder-submit-1">',
		'#suffix' => '</div>',

    );
	$form['cancel'] = array(
		'#type' => 'button',
		'#attributes' => array('onClick' => 'location.replace("'. referer_uri() .'"); return false;'),
		'#value' => t('Cancelar'),
		'#prefix' => '<div class="w20-folder-edit-folder-cancelar-1">',
		'#suffix' => '</div>',
	);
	
    return $form;
}

function w20_folder_move_form(&$form_state, $tid) {
    global $vfid;
	// o $tid desta função é o id do termo e não de seu pai
  
	$saida = db_fetch_array(db_query("SELECT t.name, t.tid, p.parent FROM {term_data} AS t LEFT JOIN {term_hierarchy} AS p ON t.tid = p.tid WHERE t.tid = '" . $tid . "' LIMIT 1 "));
  
	$children = taxonomy_get_tree(4, $tid);

    // A term can't be the child of itself, nor of its children.
    $exclude =array();
	foreach ($children as $child) {
      $exclude[] = $child->tid;
    }
    //$exclude[] = $tid;

   	$form['parent'] = _taxonomy_term_select('Mover todo o conteúdo para', 'parent', $saida['tid'], 4, '', null, null, $exclude);

    $form['tid'] = array(
		'#type' => 'hidden',
		'#value' => $tid,
	);
	
    //Submit button:
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Mover'),
		'#submit' => array('w20_folder_move_form_submit'),
		'#prefix' => '<div class="w20-folder-edit-folder-mover">',
		'#suffix' => '</div>',

    );
	$form['cancel'] = array(
		'#type' => 'button',
		'#attributes' => array('onClick' => 'location.replace("'. referer_uri() .'"); return false;'),
		'#value' => t('Cancelar'),
		'#prefix' => '<div class="w20-folder-edit-folder-cancelar-2">',
		'#suffix' => '</div>',
	);
	
    return $form;
}


function w20_folder_delete_form(&$form_state, $tid) {
    // o $tid desta função é o id do termo e não de seu pai
  
	$form['tid'] = array(
		'#type' => 'hidden',
		'#value' => $tid,
	);
	
    //Submit button:
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Excluir'),
		'#submit' => array('w20_folder_delete_form_submit'), 
		'#prefix' => '<div class="w20-folder-edit-folder-excluir-1">',
		'#suffix' => '</div>',

    );
	$form['cancel'] = array(
		'#type' => 'button',
		'#attributes' => array('onClick' => 'location.replace("'. referer_uri() .'"); return false;'),
		'#value' => t('Cancelar'),
		'#prefix' => '<div class="w20-folder-edit-folder-cancelar-3">',
		'#suffix' => '</div>',
	);
	
    return $form;
}


function w20_folder_edit_access() {
  global $user;
  return user_access('access content') && $user->uid;
    
}

function w20_folder_edit_form_validate($form, &$form_state) {
    $w20_folder_taxonomia = $form_state["clicked_button"]['#post']['name'];
    if (isset($w20_folder_taxonomia)) {
        if (!is_string($w20_folder_taxonomia) || $w20_folder_taxonomia == '') {
            form_set_error('w20_folder_taxonomia', t('Digite um nome para a pasta'));
        }
    }
}

function w20_folder_edit_form_submit($form, &$form_state) {
    
	$term = array(
		'tid' => $form_state["clicked_button"]['#post']['tid'],
		'name' => $form_state["clicked_button"]['#post']['name'], 
		'parent' => $form_state["clicked_button"]['#post']['parent'],  
	);

	$exe_query = taxonomy_save_term($term);
    if ($exe_query !== false) {
        watchdog('w20_patas', 'Added message to log', array(), WATCHDOG_INFO);
        drupal_set_message(t('Pasta editada com sucesso. '));
    } else {
        watchdog('w20_patas', 'Could not add message to log: ', array(), WATCHDOG_ERROR);
        drupal_set_message(t('A pasta não foi editada com sucesso.'));
    }
   
    $form_state['redirect'] = 'w20/folder/' . $form_state['values']['parent'];

}


function w20_folder_move_form_submit($form, &$form_state) {
    global $vfid;
	
	$term = array(
		'tid' => $form_state["clicked_button"]['#post']['tid'],
		'parent' => $form_state["clicked_button"]['#post']['parent'],  
	);

	// save all node classificated with this term
	$result = taxonomy_select_nodes(array('0' => $term['tid']), '', 0, FALSE);
    while ($row = db_fetch_object($result)) $exe_query = taxonomy_node_save(node_load($row->nid), array('0' => $term['parent']));
	
	$children = taxonomy_get_tree(4, $term['tid'], -1, 1);
    foreach ($children as $child) {
	
		$array = array('tid' => $child->tid, 'parent' => $term['parent'], 'name' => $child->name, 'vid' => $child->vid);
		taxonomy_save_term($array);
	
	}
	
	if ($exe_query !== false) {
        watchdog('w20_patas', 'Added message to log', array(), WATCHDOG_INFO);
        drupal_set_message(t('Pasta editada com sucesso. '));
    } else {
        watchdog('w20_patas', 'Could not add message to log: ', array(), WATCHDOG_ERROR);
        drupal_set_message(t('A pasta não foi editada com sucesso.'));
    }
   
    $form_state['redirect'] = 'w20/folder/' . $form_state['values']['tid'];

}


function w20_folder_delete_form_submit($form, &$form_state) {
    global $vfid;
	
	$term = array(
		'tid' => $form_state["clicked_button"]['#post']['tid'],
		'parent' => $form_state["clicked_button"]['#post']['parent'],  
	);
	
	$children = taxonomy_get_tree(4, $term['tid'], -1, null);
    foreach ($children as $child) {
		$result = taxonomy_select_nodes(array('0' => $child->tid), '', 0, FALSE);
		while ($row = db_fetch_object($result)) $exe_query = node_delete($row->nid);
		$exe_query = taxonomy_del_term($child->tid);
		drupal_set_message(t('A pasta ' . $child->name . ' foi excluída com sucesso. '));
	}
	
	$result = taxonomy_select_nodes(array('0' => $term['tid']), '', 0, FALSE);
    while ($row = db_fetch_object($result)) $exe_query = node_delete($row->nid);
	taxonomy_del_term($term['tid']);
	drupal_set_message(t('A pasta principal foi excluída com sucesso. '));
		
	if ($exe_query !== false) {
        watchdog('w20_patas', 'Added message to log', array(), WATCHDOG_INFO);
        drupal_set_message(t('Pasta excluída com sucesso. '));
    } else {
        watchdog('w20_patas', 'Could not add message to log: ', array(), WATCHDOG_ERROR);
        drupal_set_message(t('A pasta não foi excluída com sucesso.'));
    }
   
    $form_state['redirect'] = 'w20/folder/' . $form_state['values']['parent'];

}


?>
