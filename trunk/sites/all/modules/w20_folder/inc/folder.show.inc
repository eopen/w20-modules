<?php

function w20_folder_show() {
  global $user, $vfid;
  
	$tids = array();
	if (arg(2) != '') $tids[0] = arg(2); 
	else if (arg(2) == '') { 
		$tids[0] = 0; 
		$tids[1] = ''; 
	}
	$output .= '<div class="w20-folder-container"><div class="w20-folder-breadcrumb"><div class="w20-folder-breadcrumb-img-folder">'.theme('image', drupal_get_path('module', 'w20_folder') .'/img/folder.gif') . '</div> ' . w20_folder_breadcrumb(arg(2)) . '</div>';
	
	$array = taxonomy_get_tree(4, $tids[0], -1, 1);
	$output .= '<div class="w20-folder-tree-container"><div class="w20-folder-tree-folder"><ul class="w20-folder-tree-folder-ul">';
	$ctt_a = 1;
    foreach ($array as $var) {
    	$styleEvenOdd = $ctt_a % 2 == 0 ? 'w20-folder-folder-even' : 'w20-folder-folder-odd';
    	$varTextClean = w20_folder_make_my_text_clean($var -> name);
		$link =  l($var -> name, url('w20/folder/' . $var -> tid, array('absolute' => TRUE)));
		$output .= '<li class="w20-folder-tree w20-folder-folder w20-folder-folder-'.$varTextClean.' '.$styleEvenOdd.'"><div class="w20-folder-folder-img-folder">'.theme('image', drupal_get_path('module', 'w20_folder') .'/img/folder.gif') . '</div> ' . $link . '</li>';  
		$ctt_a++;
	}
	$output .= '</ul></div>';
	
	if (arg(2) > 0) {
		$result = taxonomy_select_nodes($tids, 'or', 0, FALSE);
		$output .= '<div class="w20-folder-tree-file"><ul class="w20-folder-tree-file-ul">';
		$ctt_a = 1;
		while ($row = db_fetch_object($result)) {
			$styleEvenOdd = $ctt_a % 2 == 0 ? 'w20-folder-file-even' : 'w20-folder-file-odd';
			$varTextClean = w20_folder_make_my_text_clean($row -> title);
			$link =  l($row->title, url('node/'.$row->nid, array('absolute' => TRUE)));
			$output .= '<li class="w20-folder-tree w20-folder-file w20-folder-file-'.$varTextClean.' '.$styleEvenOdd.'"><div class="w20-folder-folder-img-page">'.theme('image', drupal_get_path('module', 'w20_folder') .'/img/page.png')  . '</div> ' . $link . '</li>';  
			$ctt_a++;
		}
		$output .= '</ul></div>';
	} else {
		$result = db_query("SELECT n.nid, n.title FROM {node} AS n LEFT JOIN {term_node} AS tn ON n.nid = tn.nid LEFT JOIN {term_data} AS td ON tn.tid = td.tid WHERE td.vid IS NULL AND tn.tid IS NULL AND n.type = 'page' ORDER BY n.title ASC");
		$output .= '<div class="w20-folder-tree-file"><ul class="w20-folder-tree-file-ul">';
		$ctt_a = 1;
		while ($row = db_fetch_object($result)) {
			$styleEvenOdd = $ctt_a % 2 == 0 ? 'w20-folder-file-even' : 'w20-folder-file-odd';
			$varTextClean = w20_folder_make_my_text_clean($row -> title);
			$link =  l($row->title, url('node/'.$row->nid, array('absolute' => TRUE)));
			$output .= '<li class="w20-folder-tree w20-folder-file w20-folder-file-'.$varTextClean.' '.$styleEvenOdd.'"><div class="w20-folder-folder-img-folder">'.theme('image', drupal_get_path('module', 'w20_folder') .'/img/page.png')  . '</div> ' . $link . '</li>';  
			$ctt_a++;
		}
		$output .= '</ul></div></div>';
	}
	
	
    //$output .=  '<br />' . l(t('Criar nova página'), url('w20/folder/page/add/' . $tids[0], array('absolute' => TRUE)));
	$output .=  '<div class="w20-folder-new-buttons"><div class="w20-folder-new-container"><div class="w20-folder-new-file">' . l(t('Criar nova página'), url('node/add/page/' . $tids[0], array('query' => 'destination=w20/folder/' . $tids[0], 'absolute' => TRUE))).'</div>';
	$output .=  '<div class="w20-folder-new-folder">' . l(t('Criar nova pasta'), url('w20/folder/' . (int) $tids[0] .'/add', array('absolute' => TRUE))).'</div></div>';
	$output .= '</div></div>';
	return $output;

}  

function w20_folder_add () {

	$output .= '<div class="w20-folder-container"><div class="w20-folder-breadcrumb"><div class="w20-folder-breadcrumb-img-folder">'.theme('image', drupal_get_path('module', 'w20_folder') .'/img/folder.gif') . '</div> ' . w20_folder_breadcrumb((int) arg(2)) . '</div>';
	$output .= '<div class="w20-folder-folder-add">'.drupal_get_form('w20_folder_form', (int) arg(2)) . '</div></div>';
	
	return $output;

}


function w20_folder_access() {
  global $user;
  return user_access('access content') && $user->uid;
    
}


function w20_folder_form(&$form_state, $parent) {
    // o $tid desta função, é o id do termo pai
  
	$form['name'] = array(
		'#type' => 'textfield',
		'#title' => t('Criar nova pasta'),
		'#size' => 30,
		'#maxlength' => 30,
		'#prefix' => '<div class="w20-folder-add-folder-new">',
		'#suffix' => '</div>',
	);

	$form['parent'] = array(
		'#type' => 'hidden',
		'#title' => '', 
		'#value' => $parent,
	);
	
    //Submit button:
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Salvar'),
		'#submit' => array('w20_folder_form_submit'), 
		'#prefix' => '<div class="w20-folder-add-folder-submit">',
		'#suffix' => '</div>',

	);
	$form['cancel'] = array(
		'#type' => 'button',
		'#attributes' => array('onClick' => 'location.replace("'. referer_uri() .'"); return false;'),
		'#value' => t('Cancelar'), 
		'#prefix' => '<div class="w20-folder-add-folder-cancel">',
		'#suffix' => '</div>',
	);


   
    return $form;
}

function w20_folder_form_validate($form, &$form_state) {
    $w20_folder_taxonomia = $form_state['values']['name'];
    if (isset($w20_folder_taxonomia)) {
        if (!is_string($w20_folder_taxonomia) || $w20_folder_taxonomia == '') {
            form_set_error('w20_folder_taxonomia', t('Digite um nome pra pasta'));
        }
    }
}

function w20_folder_form_submit($form, &$form_state) {
    global $vfid;
	
	$term = array(
		'vid' => 4, // Voacabulary ID
		'name' => $form_state['values']['name'], // Term Name
		'parent' => $form_state['values']['parent'], // (Optional) Term ID of a parent term 
	);

	$exe_query = taxonomy_save_term($term);
    $last_id = db_last_insert_id('{test_module_log}','id');
    if ($exe_query !== false) {
        watchdog('w20_patas', 'Added message to log: %id', array('%id'=>$last_id), WATCHDOG_INFO);
        drupal_set_message(t('Pasta criada com sucesso. '));
    } else {
        watchdog('w20_patas', 'Could not add message to log: ', array(), WATCHDOG_ERROR);
        drupal_set_message(t('A pasta não foi salva com sucesso.'));
    }

	
    $form_state['redirect'] = 'w20/folder/' . $form_state['values']['parent'];
	
}

?>
